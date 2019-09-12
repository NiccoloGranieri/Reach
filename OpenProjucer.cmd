PUSHD JUCE\extras\Projucer\Builds\VisualStudio2019
SET CL=/DJUCER_ENABLE_GPL_MODE
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" Projucer.sln /p:Configuration=Release
start x64\Release\App\Projucer.exe
POPD
exit