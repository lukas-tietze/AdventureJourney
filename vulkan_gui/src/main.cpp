#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "exception.hpp"
#include "data/string.hpp"
#include "data/math.hpp"

#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

namespace
{
struct QueueFamilyIndices
{
    int graphics = -1;
    int presentation = -1;

    bool is_complete()
    {
        return graphics >= 0 && presentation >= 0;
    }
};

struct SwapChainDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

GLFWwindow *window;
VkInstance instance;

std::vector<const char *> requiredLayers;
std::vector<const char *> requiredExtensions;
std::vector<const char *> requiredDeviceExtensions;

constexpr bool enableValidationLayers = true;
constexpr bool enableCallback = true;
constexpr uint32_t windowWidth = 800;
constexpr uint32_t windowHeight = 450;

VkDebugUtilsMessengerEXT callback;
VkPhysicalDevice physical_device;
VkDevice device;
VkQueue graphics_queue;
VkQueue presentation_queue;
VkSurfaceKHR surface;
VkSwapchainKHR swapChain;
QueueFamilyIndices family_indices;
SwapChainDetails chain_details;
} // namespace

void init_window()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(800, 450, "Vulkan Test", nullptr, nullptr);
}

void gather_required_layers()
{
    requiredLayers.push_back("VK_LAYER_LUNARG_standard_validation");

    std::printf("Requiring layers:\n");

    for (const auto &layer : requiredLayers)
    {
        std::printf("- %s\n", layer);
    }
}

void validate_vk_layers()
{
    gather_required_layers();

    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const auto &requiredLayer : requiredLayers)
    {
        bool found = false;

        for (const auto &availableLayer : availableLayers)
        {
            if (std::strcmp(requiredLayer, availableLayer.layerName) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            throw util::exception(util::format("Could not find required layer \"%s\"!", requiredLayer));
        }
    }

    std::printf("Available layers:\n");

    for (const auto &layer : availableLayers)
    {
        std::printf("- %s\n", layer.layerName);
    }
}

void gather_required_device_extensions()
{
    requiredDeviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
}

bool validate_required_device_extensions(VkPhysicalDevice device)
{
    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);

    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    for (const auto &requiredExtension : requiredDeviceExtensions)
    {
        bool found = false;

        for (const auto &availableExtension : availableExtensions)
        {
            if (std::strcmp(requiredExtension, availableExtension.extensionName) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            return false;
        }
    }
}

void gather_required_extensions()
{
    uint32_t extensionCount = 0;
    const char **requiredInstanceExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

    requiredExtensions.assign(requiredInstanceExtensions, requiredInstanceExtensions + extensionCount);

    if (enableValidationLayers)
        requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    std::printf("Requiring extensions:\n");

    for (const auto &extension : requiredExtensions)
    {
        std::printf("- %s\n", extension);
    }
}

void validate_vk_extensions()
{
    gather_required_extensions();

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);

    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

    for (const auto &requiredExtension : requiredExtensions)
    {
        bool found = false;

        for (const auto &availableExtension : availableExtensions)
        {
            if (std::strcmp(requiredExtension, availableExtension.extensionName) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            throw util::exception(util::format("Could not find required extension \"%s\"!", requiredExtension));
        }
    }

    std::printf("Found following availableExtensions:\n");

    for (const auto &extension : availableExtensions)
    {
        std::printf("- %s\n", extension.extensionName);
    }
}

void create_vk_instance()
{
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Test";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    if (enableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(requiredLayers.size());
        createInfo.ppEnabledLayerNames = requiredLayers.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    {
        throw util::exception("Failed to initialize Vulkan!");
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                              VkDebugUtilsMessageTypeFlagsEXT messageType,
                                              const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                              void *pUserData)
{
    std::printf("debug callback:%s\n", pCallbackData->pMessage);
}

void destroy_callback()
{
    if (!enableCallback)
        return;

    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)
        vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

    if (func != nullptr)
        func(instance, callback, nullptr);
}

void init_callback()
{
    if (!enableCallback)
        return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    createInfo.sType =
        VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType =
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debug_callback;
    createInfo.pUserData = nullptr;

    auto f = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

    if (f != nullptr)
    {
        if (f(instance, &createInfo, nullptr, &callback) != VK_SUCCESS)
            throw util::exception("Failed to init debug callback!");
    }
    else
    {
        std::printf("Could not find debug extension!\n");
    }
}

QueueFamilyIndices find_queue_families(VkPhysicalDevice device)
{
    QueueFamilyIndices res = {};
    uint32_t indices = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(device, &indices, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(indices);

    vkGetPhysicalDeviceQueueFamilyProperties(device, &indices, queueFamilies.data());

    int i = 0;
    for (const auto &queueFamily : queueFamilies)
    {
        if (queueFamily.queueCount > 0)
        {
            if (res.graphics < 0 && (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT))
            {
                res.graphics = i;
            }

            VkBool32 presentationSupport = VK_FALSE;

            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentationSupport);

            if (presentationSupport)
            {
                res.presentation = i;
            }
        }

        if (res.is_complete())
            break;
    }

    return res;
}

SwapChainDetails query_swap_chain_details(VkPhysicalDevice device)
{
    SwapChainDetails res;

    uint32_t formatCount;
    uint32_t presentModeCount;

    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    if (formatCount > 0)
    {
        res.formats.resize(formatCount);

        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, res.formats.data());
    }

    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    if (presentModeCount > 0)
    {
        res.presentModes.resize(presentModeCount);

        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, res.presentModes.data());
    }

    return res;
}

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
{
    if (availableFormats.size() == 1 &&
        availableFormats[0].format == VK_FORMAT_UNDEFINED)
        return availableFormats[0];

    for (const auto &format : availableFormats)
    {
        if (format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR &&
            format.format == VK_FORMAT_B8G8R8A8_UNORM)
            return format;
    }

    return availableFormats[0];
}

VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
{
    if (std::find(availablePresentModes.begin(), availablePresentModes.end(), VK_PRESENT_MODE_MAILBOX_KHR) != availablePresentModes.end())
        return VK_PRESENT_MODE_MAILBOX_KHR;

    if (std::find(availablePresentModes.begin(), availablePresentModes.end(), VK_PRESENT_MODE_IMMEDIATE_KHR) != availablePresentModes.end())
        return VK_PRESENT_MODE_IMMEDIATE_KHR;

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        return capabilities.currentExtent;
    }
    else
    {
        VkExtent2D res = {};

        res.width = util::crop(windowWidth,
                               capabilities.minImageExtent.width,
                               capabilities.maxImageExtent.width);

        res.height = util::crop(windowHeight,
                                capabilities.minImageExtent.height,
                                capabilities.maxImageExtent.height);

        return res;
    }
}

bool is_device_suitable(VkPhysicalDevice device)
{
    auto families = find_queue_families(device);
    auto swapChainDetails = query_swap_chain_details(device);

    return families.is_complete() &&
           !swapChainDetails.formats.empty() &&
           !swapChainDetails.presentModes.empty() &&
           validate_required_device_extensions(device);
}

void pick_physical_device()
{
    gather_required_device_extensions();

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0)
        throw util::exception("Failed to find Devices that support Vulkan!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    std::printf("Found devices:\n");
    bool suitableDeviceFound = false;
    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;

    for (const auto &device : devices)
    {
        vkGetPhysicalDeviceProperties(device, &properties);
        vkGetPhysicalDeviceFeatures(device, &features);

        std::printf("- %s\n", properties.deviceName);

        if (!suitableDeviceFound && is_device_suitable(device))
        {
            physical_device = device;
            family_indices = find_queue_families(physical_device);
            suitableDeviceFound = true;
        }
    }

    if (!suitableDeviceFound)
    {
        throw util::exception("No suitable Device found!");
    }
}

void create_logical_device()
{
    float queuePriorities = 1.f;

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

    for (int i : std::set<int>{family_indices.graphics, family_indices.presentation})
    {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = family_indices.graphics;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriorities;

        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures physicalDeviceFeatures = {};

    VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
    deviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;
    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredDeviceExtensions.size());
    deviceCreateInfo.ppEnabledExtensionNames = requiredDeviceExtensions.data();

    if (enableValidationLayers)
    {
        deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(requiredLayers.size());
        deviceCreateInfo.ppEnabledLayerNames = requiredLayers.data();
    }
    else
    {
        deviceCreateInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physical_device, &deviceCreateInfo, nullptr, &device) != VK_SUCCESS)
        throw util::exception("Failed to create logical device!");
}

void create_queues()
{
    vkGetDeviceQueue(device, family_indices.graphics, 0, &graphics_queue);
    vkGetDeviceQueue(device, family_indices.presentation, 0, &presentation_queue);
}

void create_surface()
{
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
        throw util::exception("Failed to create surface!");
}

void create_swap_chain()
{
    SwapChainDetails details = query_swap_chain_details(physical_device);
    VkSurfaceFormatKHR format = chooseSwapSurfaceFormat(details.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(details.presentModes);
    VkExtent2D extent = chooseSwapExtent(details.capabilities);

    uint32_t imageCount = details.capabilities.minImageCount + 1;

    if (details.capabilities.maxImageCount > 0 &&
        imageCount > details.capabilities.maxImageCount)
    {
        imageCount = details.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR info = {};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    info.surface = surface;
    info.minImageCount = imageCount;
    info.imageFormat = format.format;
    info.imageColorSpace = format.colorSpace;
    info.imageExtent = extent;
    info.imageArrayLayers = 1;
    info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    uint32_t queueFamilyIndices[] = {family_indices.presentation, family_indices.graphics};

    if (family_indices.graphics != family_indices.presentation)
    {
        info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        info.queueFamilyIndexCount = 2;
        info.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
    {
        info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        info.queueFamilyIndexCount = 0;
        info.pQueueFamilyIndices = nullptr;
    }

    info.preTransform = details.capabilities.currentTransform;
    info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    info.presentMode = presentMode;
    info.clipped = VK_TRUE;
    info.oldSwapchain = VK_NULL_HANDLE;

    if (int x = vkCreateSwapchainKHR(device, &info, nullptr, &swapChain) != VK_SUCCESS)
        throw util::exception("Failed to create Swapchain!" + std::to_string(x));
}

void init_vulkan()
{
    validate_vk_layers();
    validate_vk_extensions();
    create_vk_instance();
    init_callback();

    create_surface();
    pick_physical_device();
    create_logical_device();
    create_queues();
    create_swap_chain();
}

void main_loop()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

////vllt. eher dispose
void cleanup()
{
    destroy_callback();

    vkDestroySwapchainKHR(device, swapChain, nullptr);
    vkDestroyDevice(device, nullptr);
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);

    glfwTerminate();
}

int main()
{
    try
    {
        init_window();
        init_vulkan();
        main_loop();
        cleanup();
    }
    catch (std::exception &e)
    {
        std::printf("Failure: %s\n", e.what());

        return EXIT_FAILURE;
    }
    catch (util::exception &e)
    {
        std::printf("Failure: %s\nAt:\n%s\n",
                    e.get_message().c_str(),
                    util::format_stacktrace(e.get_stacktrace(), 4, -1).c_str());

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}