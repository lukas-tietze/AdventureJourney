$BUILD_DIR = ".\build\"
$RELEASE_DIR = $BUILD_DIR + "release\"
$DEBUG_DIR = $BUILD_DIR + "debug\"

function Info {
    param([string]$msg)

    Write-Host $($(Get-Date), ">", $msg) -ForegroundColor Green
}

function Warn {
    param([string]$msg)

    Write-Host $($(Get-Date), ">", $msg) -ForegroundColor Yellow
}

function Err {
    param([string]$msg)

    Write-Host $($(Get-Date), ">", $msg) -ForegroundColor Red
}

if (-not(Test-Path $BUILD_DIR)) {
    New-Item -Path $BUILD_DIR -ItemType Directory;
}

if (-not(Test-Path $DEBUG_DIR)) {
    New-Item -Path $DEBUG_DIR -ItemType Directory;
}

if (-not(Test-Path $RELEASE_DIR)) {
    New-Item -Path $RELEASE_DIR -ItemType Directory;
}

$input = Read-Host 
$param = ""
$mode = "debug"

while (-not($input -eq "quit") -and -not($input -eq "q")) {
    $splitInput = $input.Split(' ')
    $arg = $splitInput[0];

    if ($splitInput.Length -ge 1) {
        $param = $splitInput[1]
    }
    else {
        $param = ""
    }    

    Write-Host "Input was $arg"

    switch ($arg) {
        "mode" {
            Info "Setting mode to $mode"

            mode = $param
        }

        "gen" {
            Info "Generating Buildfiles..."
    
            Set-Location $BUILD_DIR\$mode
            cmake -DCMAKE_BUILD_TYPE=Debug "..\.."
            Set-Location "..\.."
        }
    
        "build" {
            Info "Building project..."
    
            Set-Location $DEBUG_DIR
            cmake --build .
            Set-Location "..\.."
        }
    
        "sync" {
            Info "Syncing..."
    
            git pull
            git push
            git status
        }
    
        "clean" {
            Info "Cleaning up build files..."
    
            Remove-Item -Path $BUILD_DIR -Recurse -Force 
        }
    
        "trace" {
            Info "Tracing program..."
            Err "Not implemented!"
        }
        
        "run" {
            Info "Running program..."
            
            .\build\debug\Debug\Gui.exe
        }
    
        "todo" {
            Info "Showing Todos..."
            Err "Not implemented!"
        }
        Default { Warn "Unknown task '$arg'" }       
    }

    $input = Read-Host 
}