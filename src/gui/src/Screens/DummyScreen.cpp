#include "GlScreens.hpp"
#include "DummyData.hpp"
#include "data/Io.hpp"
#include "glm/gtx/transform.hpp"
#include "data/Random.hpp"
#include "graphics/Color.hpp"

namespace
{
constexpr char MAIN_LIGHT[] = "MAIN_LIGHT";

struct TextureBuilder
{
    uint32_t operator()(float x, float y) const
    {
        return util::Color(x * (1 - y), x * (1 - y), x * y * (1 - x) * (1 - y)).Value();
    }
};

struct NormalMapBuilder
{
    uint32_t operator()(float x, float y) const
    {
        return util::Color(x * (1 - y), x * (1 - y), x * y * (1 - x) * (1 - y)).Value();
    }
};
} // namespace

gui::DummyScreen::DummyScreen() : DebugScreenBase()
{
    auto lights = this->scene.GetLightSet(MAIN_LIGHT);
    lights->SetBindingTarget(4);
    auto &light = lights->Add();
    light.SetActive(true);
    light.SetAmbientFactor(0.3f);
    light.SetColor(glm::vec3(1.0f, 1.0f, 1.0f) * 0.75f);
    light.SetPosition(glm::vec3(0.f, 1.f, 0.f));
    light.SetType(glutil::LightType::Point);
    this->scene.SetActiveLightSet(MAIN_LIGHT);
    lights->CreateGlObjects();

    auto bmf = this->scene.GetFont("BMF");
    bmf->Load("assets/fonts/BMFTest.json");

    auto ttf = this->scene.GetFont("TTF");
    ttf->Load("assets/fonts/TTFTest.json");

    auto grassTex = this->scene.GetTexture("Grass");
    grassTex->SetMinFilterMode(GL_LINEAR_MIPMAP_LINEAR);
    grassTex->SetMipmapsEnabled(true);
    grassTex->LoadData("assets/textures/grass.png");

    auto pebbleTex = this->scene.GetTexture("Pebble");
    pebbleTex->SetMinFilterMode(GL_LINEAR_MIPMAP_LINEAR);
    pebbleTex->SetMipmapsEnabled(true);
    pebbleTex->LoadData("assets/textures/pebble.png");

    auto gridTex = this->scene.GetTexture("Grid");
    gridTex->SetMinFilterMode(GL_LINEAR_MIPMAP_LINEAR);
    gridTex->SetMipmapsEnabled(true);
    gridTex->LoadData("assets/textures/CubeGrid.png");

    auto numGridTex = this->scene.GetTexture("NumGrid");
    numGridTex->SetMinFilterMode(GL_LINEAR_MIPMAP_LINEAR);
    numGridTex->SetMipmapsEnabled(true);
    numGridTex->LoadData("assets/textures/Numbered Grid.png");

    auto grassMaterial = this->scene.GetMaterial("Grass");
    grassMaterial->SetAlbedo(glm::vec4(0.3f, 0.8f, 0.5f, 1.f));
    grassMaterial->SetAlbedoMap(grassTex, GL_TEXTURE0);

    auto pebbleMaterial = this->scene.GetMaterial("Pebble");
    pebbleMaterial->SetAlbedo(glm::vec4(0.3f, 0.3f, 0.3f, 1.f));
    pebbleMaterial->SetAlbedoMap(pebbleTex, GL_TEXTURE0);

    auto gridMaterial = this->scene.GetMaterial("Grid");
    gridMaterial->SetAlbedo(glm::vec4(0.3f, 0.3f, 0.3f, 1.f));
    gridMaterial->SetAlbedoMap(gridTex, GL_TEXTURE0);

    auto numGridMaterial = this->scene.GetMaterial("NumGrid");
    numGridMaterial->SetAlbedo(glm::vec4(0.3f, 0.3f, 0.3f, 1.f));
    numGridMaterial->SetAlbedoMap(numGridTex, GL_TEXTURE0);

    auto fontMaterial = this->scene.GetMaterial("Font");
    fontMaterial->SetAlbedo(glm::vec4(0.f, 0.f, 0.f, 1.f));
    fontMaterial->SetAlbedoMap(bmf->GetTexture(), GL_TEXTURE0);

    auto testMaterial = gridMaterial;

    auto textMesh = this->scene.GetMesh("Text");
    bmf->CreateStringMesh("OpenGl Rocks!", textMesh);

    auto floorMesh = this->scene.GetMesh("Floor");
    gui::quadrics::Quad(*floorMesh);

    auto icoMesh = this->scene.GetMesh("IcoMesh");
    gui::quadrics::IcoSphere(3, *icoMesh);

    auto uvMesh = this->scene.GetMesh("UvMesh");
    gui::quadrics::UvSphere(32, 20, *uvMesh);

    auto diskMesh = this->scene.GetMesh("DiskMesh");
    gui::quadrics::Disk(32, 1, *diskMesh);

    auto cubeMesh = this->scene.GetMesh("CubeMesh");
    gui::quadrics::Box(*cubeMesh);

    auto cylinderMesh = this->scene.GetMesh("CylinderMesh");
    gui::quadrics::Cylinder(32, 1, *cylinderMesh);

    auto coneMesh = this->scene.GetMesh("ConeMesh");
    gui::quadrics::Cone(32, 3, *coneMesh);

    auto textObj = this->scene.GetObject("Text");
    textObj->SetGeometry(textMesh);
    textObj->SetModelMatrix(glm::translate(glm::vec3(0.f, 3.f, 0.f)) * glm::scale(glm::vec3(5.f, 5.f, 5.f)));
    textObj->SetBindingTarget(2);
    textObj->SetMaterial(fontMaterial);
    textObj->CreateGlObjects();

    auto floorObj = this->scene.GetObject("Floor");
    floorObj->SetGeometry(floorMesh);
    floorObj->SetModelMatrix(glm::scale(glm::vec3(5, 5, 5)));
    floorObj->SetBindingTarget(2);
    floorObj->SetMaterial(pebbleMaterial);
    floorObj->CreateGlObjects();

    auto lamp = this->scene.GetObject("Lamp");
    lamp->SetGeometry(icoMesh);
    lamp->SetModelMatrix(glm::translate(glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(0.1, 0.1, 0.1)));
    lamp->SetBindingTarget(2);
    lamp->SetMaterial(grassMaterial);
    lamp->CreateGlObjects();

    auto ico = this->scene.GetObject("Ico");
    ico->SetGeometry(icoMesh);

    auto uv = this->scene.GetObject("Uv");
    uv->SetGeometry(uvMesh);

    auto disk = this->scene.GetObject("Disk");
    disk->SetGeometry(diskMesh);

    auto cube = this->scene.GetObject("Cube");
    cube->SetGeometry(cubeMesh);

    auto cylinder = this->scene.GetObject("Cylinder");
    cylinder->SetGeometry(cylinderMesh);

    auto cone = this->scene.GetObject("Cone");
    cone->SetGeometry(coneMesh);

    std::vector<glutil::SceneObject *> objects = {
        cylinder,
        cone,
        cube,
        disk,
        ico,
        uv,
    };

    for (size_t i = 0; i < objects.size(); i++)
    {
        auto obj = objects[i];

        obj->SetModelMatrix(glm::translate(glm::vec3(1.f, 1.f, static_cast<float>(objects.size()) / 2.f - static_cast<float>(i))) * glm::scale(glm::vec3(0.3f, 0.3f, 0.3f)));
        obj->SetMaterial(testMaterial);
        obj->SetBindingTarget(2);
        obj->CreateGlObjects();
    }
}

gui::DummyScreen::~DummyScreen()
{
}

void gui::DummyScreen::BeforeRender()
{
}

void gui::DummyScreen::AfterRender()
{
}

void gui::DummyScreen::BeforeUpdate()
{
}

void gui::DummyScreen::AfterUpdate()
{
}