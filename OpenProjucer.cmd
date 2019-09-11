PUSHD JUCE\extras\Projucer\Builds\VisualStudio2019
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" Projucer.sln /p:Configuration=Release /p:JUCER_ENABLE_GPL_MODE=1
start x64\Release\App\Projucer.exe
POPD
exit