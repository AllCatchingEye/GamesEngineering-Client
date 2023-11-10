# Schafkopf UE5 Client

## 1 Project setup

In order to develop the UE5 client of Schafkopf, a few components need to be installed first.
If you only want to program in the Unreal Editor using the blueprint system, then only the
[primary setup](#11-unreal-editor-only) step is neccessary. However if coding in C++ is desired
too, then both the first and [secondary setup](#12-unreal-editor-and-c) steps are required.
The reason for this is, that a few things can only be done in the editor, while C++ should be
used when performance is key. For more information see the respective setup steps.

### 1.1 Unreal Editor only

This initial setup allows you to program in the Unreal Engine editor via the blueprint system.
The editor is for example needed for configuring the project's standard settings, creating
levels/maps and importing 3D objects and other resources. It is also needed to create UIs or
generate the boilerplate code for new C++ files.

For this the following software needs to be installed:
1. [Git](https://git-scm.com/downloads) as source control software.
2. [Git LFS](https://git-lfs.com/) to separately handles large files in source control.\
	Once the plugin is installed, execute `git lfs install` to setup Git LFS.
3. Unreal Engine 5.3.1 via the Epic Games Launcher.

### 1.2 Unreal Editor and C++

Additionally, if you want to program in C++, a few more things need to be setup. C++ code should
be used when performance is key, as it is more performant than code created in the blueprint
editor. Furthermore, the use of C++ enables a more advanced architecture than blueprints and
possibilities that are not available for use in the Unreal Editor. For expample, a few features
like multidimensional/nested arrays or a broader access to the Unreal Enginge's API, general
C++ language features or libraries may only be used in C++. Using C++ also allows us to encapsulate
these features for use in blueprints or create base classes that may be expanded by blueprints.

As recommended by Epic Games, this project will use Microsoft Visual Studio for creating code in
C++. Thus this guide will only target MS Visual Studio:
1. Install the `Visual Studio Integration Tool` via the Unreal Engine Marketplace.
2. Install `Microsoft Visual Studio 2022` (the Communtiy version is free) or modify an existing
	installation.
	1. Under `Workloads` tab, select at least `Game development with C++`.
	2. In the Installations details pane, ensure that under Game development with C++ > Optional
	that IDE support for Unreal Engine is selected.\
	This installs what this article refers to as the Visual Studio Tools for Unreal Engine. If you
	work with the High-Level Shader Language, ensure that HLSL Tools is also selected.
	3. Select the Individual components tab at the top of the dialog.
	4. Under Installation details, expand Desktop development with C++.
	5. Ensure that under Optional that Windows 10 SDK 10.0.18362.0, or higher, is selected.
3. Once the installation is done, to generate the Visual Studo files, open the project in the
	file explorer. Right-click the `.uproject` file and select `Generate Visual Studio project files`.

Source: [Install Visual Studio Tools for Unreal Engine](https://learn.microsoft.com/en-us/visualstudio/gamedev/unreal/get-started/vs-tools-unreal-install), last accessed: 2023.10.27.

Additionally, it is recommended to make a few adjustments to the editor preferences, to ease
coding with the editor and C++:
1. Disable `Automatically Compile Newly Added C++ Classes`:\
	Under `Edit > Editor Preferences > Miscellaneous > Hot Reload` disable said setting.
	This will ensure that when creating a new C++ class through the Editor, only the
	necessary files will be generated. This prevents the Editor from automatically initiating
	a recompilation of the entire project, simply because a relatively empty file was added
	to the project. Otherwise prepare yourself for waiting multiple minutes for a process
	that will likely fail.
2. Disable `Enable Live Coding`:\
	Under `Edit > Editor Preferences > Live Coding > General` disable said setting.

## 2 Style and coding conventions

Unreal Engine 5 has its own style and coding conventions, to which we too shall adhere to.
Strictly, as if it were the law. The following sources give an overview of the Unreal Engine's
style and coding conventions and project structure:

- [UE5 style guide](https://github.com/Allar/ue5-style-guide)
- [UE5 gitignore](https://github.com/MOZGIII/ue5-gitignore)
