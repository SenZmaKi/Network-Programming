
function ExitIfError {
    if ($LASTEXITCODE -ne 0) {
      throw "Error encountered exiting.. ."
    }
  }

function CheckAndInstallTool {
    param (
        [Parameter(Mandatory=$true)]
        [string]$toolName,
        [Parameter(Mandatory=$true)]
        [string]$installCommand
    )

    try {
        Get-Command $toolName -ErrorAction Stop | Out-Null
        Write-Output "$toolName is already installed."
    } catch {
        Write-Output "$toolName is not installed."
        Write-Output "Installing $toolName..."
        Invoke-Expression $installCommand
        ExitIfError
    }
}


echo ""
echo "Setting up project"
echo "Installing C++ dev tools: clang 17.0.6+, make 4.4.1+"
echo "Installation tools: winget, git, choco"
CheckAndInstallTool -toolName "git" -installCommand "winget install Git.Git"
CheckAndInstallTool -toolName "clang" -installCommand "winget install LLVM.LLVM"
CheckAndInstallTool -toolName "choco" -installCommand "winget install Chocolatey.Chocolatey"
CheckAndInstallTool -toolName "make" -installCommand "choco install make"

echo ""
echo "Cloning Repo"
git clone https://github.com/SenZmaKi/Network-Programming.git
ExitIfError
cd Network-Programming/Assignment-1

echo "Installing dependencies"
echo "Installing asio-1.28.0"
git clone --depth 1 --branch asio-1-28-0 https://github.com/chriskohlhoff/asio.git include/asio-1.28.0
ExitIfError
Remove-Item -Recurse -Force include/asio-1.28.0/.git
ExitIfError

echo ""
echo "Setup complete"
echo "From Network-Programming/Assignment-1"
echo "To run the server: make run_server"
echo "To run the client: make run_client"
echo "To run the standalone program: make run_standalone"
echo "Clean previous builds: make clean"
echo "You also need to manually install MSVC C++ Build tools: https://github.com/bycloudai/InstallVSBuildToolsWindows"
try {
  Get-Command "rm" -ErrorAction Stop | Out-Null
}
catch {
  $gitPath = (Get-Command git).Source
  $gitDir = Split-Path (Split-Path $gitPath)
  $binDir = Join-Path $gitDir "usr/bin"
  echo "'make clean' needs the 'rm' command added to PATH. Please use git bash or add the following directory to your PATH: $binDir."
}
echo "Find more Make tasks at https://github.com/SenZmaKi/Network-Programming/blob/master/README.md#make"

