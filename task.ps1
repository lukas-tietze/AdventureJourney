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

foreach ($arg in $args) {
    Write-Host $arg

    switch ($arg) {
        "gen" {
            Info "Generating Buildfiles..."
    
            Set-Location $DEBUG_DIR
            cmake -DCMAKE_BUILD_TYPE=Debug "..\.."
            Set-Location "..\.."
        }
    
        "build" {
            Info "Building project..."
    
            MSBuild.exe -nr:true -m "./build/debug/GalaxyAtWar.sln"
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

    if (-not $?) {
        Err "Error in last step, stopping..."

        break;
    }
}