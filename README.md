# Schafkopf UE5 Client

## 1 Project setup

In order to develop the UE5 client of Schafkopf, a few components need to be installed first.
If you only want to program in the Unreal Editor using the blueprint system, then only the
[primary setup](#11-unreal-editor-only) step is neccessary. However if coding in C++ is desired
too, then both the first and [secondary setup](#12-unreal-editor-and-c) steps are required.
The reason for this is, that a few things can only be done in the editor, while C++ should be
used when performance is key. For more information see the respective setup steps.

### 1.1 Unreal Editor only

This initial setup allows you to program in the Unreal Engine editor via the blueprint system:
1. [Git](https://git-scm.com/downloads) as source control software.
2. [Git LFS](https://git-lfs.com/) to handles large files.  
    Once the plugin is installed, execute `git lfs install` to setup Git LFS.
3. Unreal Engine 5.3.1 via the Epic Games Launcher.

### 1.2 Unreal Editor and C++

Additionally, if you want to program in C++, a few more things need to be setup, since the
Visual Studio project files will be generate by the Unreal Engine:
1. Install the `Visual Studio Integration Tool` via the Unreal Engine Marketplace.
2. Install `Microsoft Visual Studio 2022` (the Communtiy version is free). Under `Workloads`,
  select at least `Game development with C++`.
3. Once the installation is done, open the project in the file explorer. Right-click the
  `.uproject` file and select `Generate Visual Studio project files`.

Source: [Install Visual Studio Tools for Unreal Engine](https://learn.microsoft.com/en-us/visualstudio/gamedev/unreal/get-started/vs-tools-unreal-install)

## 2 Style and coding conventions

Unreal Engine 5 has its own style and coding conventions, to which we too shall adhere to.
Strictly, as if it were the law. The following sources give an overview of the Unreal Engine's
style and coding conventions and project structure:

- [UE5 style guide](https://github.com/Allar/ue5-style-guide)
- [UE5 gitignore](https://github.com/MOZGIII/ue5-gitignore)
