# Snake
This snake game was done as a project for our applied programming course. We are in our third semester of computer engineering. It was done by using OpenGL, glut library and in C language on visual studio. In order for this code to run successfully on your compiler, you need to install the OpenGL, glut library through this link. <https://www.opengl.org/resources/libraries/glut/glut_downloads.php>. After that, scroll down until you find the link of glutdlls37beta.zip. Download the files and once you do, open its folder. You’ll find several libraries you’re gonna need to add to differents paths. First, for the “glut.lib and glut32.lib”: 
1-C:/program files (x86)/visual studio/year of your visual studio/community/VC/Auxiliary/VS/lib/x64 
2- C:/program files (x86)/visual studio/year of your visual studio/community/VC/Auxiliary/VS/lib/x86

Next for the “glut.h”: 
1. C:/program files (x86)/visual studio/year of your visual studio/community/VC/Auxiliary/VS/include/gl

And finally for the “glut32.dll” 
1. C:/Windows/system32
2. C:/windows/sysWOW64

Once you’re done, you’re going to need to open your visual studio. Make sure to include the <windows.h> library as well as <glut.h> library for your C compiler. Make sure your visual studio is set to x86 and not x64. Then you’re all good to go.
