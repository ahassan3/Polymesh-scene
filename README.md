# WindowsGLFW
C++ Visual Studio OpenGL/GLFW starter project

## Instructions

1. Open the WindowsGLWF.sln Visual Studio solution file.

2. Choose the Project -> Manage NuGet Packages menu to open the NuGet manager.

3. Press the Restore button near the top right corner of the window to restore the missing NuGet packages. Close the NuGet manager.

4. Press F5 (or the Debug/Run icon) and the project should now build and run. Pressing the f key will draw filled triangles, pressing the l (letter l, not number 1) key to draw as lines, and press the p key to draw as points. Press the q key or Esc key to quit.

## Additional instructions if it does not find the shader files

1. Use Windows Explorer to navigate into the WindowsGLFW subdirectory within the top-level WindowsGLFW directory (so you can see the vshader.txt and fshader.txt files). Right click on the path bar and choose the option to copy address as text.

2. Follow the instructions here: http://www.computerhope.com/issues/ch000549.htm to create an environment variable with the name GL\_SHADER\_DIR and paste in the path from the previous instruction as the value for that variable.

2. If Visual Studio was running, you need to quit it and re-launch it for it to get the updated environment variable. Afer quitting and relaunching Visual Studio, press F5 (od the Debug/Run icon).
