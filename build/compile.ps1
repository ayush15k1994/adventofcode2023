param(
    [Parameter(Mandatory)]
    [string]$dir,

    [Parameter(Mandatory)]
    [string]$file,

    [Parameter()]
    [string]$output="a"
)

$file = "..\${dir}\${file}.cpp";

if (!(Test-Path -PathType Container $dir)) {
    New-Item -ItemType Directory $dir
}

g++ -g $file -std=c++20 -O2 -Wall -o "./${dir}/${output}.exe";
g++ -g $file -std=c++20 -O2 -Wall -o "./run.exe";
