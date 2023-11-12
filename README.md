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

- [UE5 coding standard] (https://docs.unrealengine.com/5.3/en-US/epic-cplusplus-coding-standard-for-unreal-engine)
- [UE5 style guide](https://github.com/Allar/ue5-style-guide)
- [UE5 gitignore](https://github.com/MOZGIII/ue5-gitignore)

## 3 Programming tips and tricks

Furthermore the are a few tips and tricks, that ease the flow of programming for both C++ and the
Editor.

### 3.1 Refactoring C++ code or Blueprint assets

The refactoring of C++ code inside an Unreal Engine project is quite different from refactoring code
normally. Simply renaming a file, class, function, etc. will cause severe incompatibilities.

Before refactoring, make sure to commit all changes, so that you can easily make a rollback. And do
forget to rebuild the project afterwards. Now to the actual refactoring:

#### 3.1.1 Refactoring of C++ files that are not used in the editor

1. Delete, rename or move the `.h` and `.cpp` files. Do not forget to adapt the includes.\
	In case of renameing the file, change the corresponding classname too. Respect UE conventions.
2. Close Visual Studio
3. Generate the project files by right clicking the `.uproject` file and selecting `Generate Visual Studio project files`.\
	Optionally, delete the `Binaries`, `DerivedDataCache` and `Intermediate` folders for a clean regeneration.

#### 3.1.2 Refactoring of C++ files that are used in the editor

In case of files/objects that are used inside the editor, but were deleted, moved or renamed, the
editor will no longer find the new file or object under the old name. This will result in either the
blueprint code, C++ code or both, failing compilation. To address this issue, Unreal Engine uses
[Core Redirects](https://docs.unrealengine.com/5.3/en-US/core-redirects-in-unreal-engine). Also see
[Core Redirects - Community Wiki](https://unrealcommunity.wiki/core-redirects/jwjn8ogt).

If you intend to delete the file do these steps first:
1. In the editor's content browser navigate to the file you want to delete.
2. Right click the file and select `References > Reference Viewer...`.
3. Remove all references in your maps and assets to the file you want to delete.
4. Remove all references in your C++ code.
5. Delete the file/object.

If you wish to change the filename/classname, complete the following steps either manually or through
a refactoring tool:
1. Change the filename of the `.h` and `.cpp` files. Do not forget to adapt the includes.
2. Change the classname to correspond to the new filename. Respect UE conventions.
3. Open the `Config/DefaultEngine.ini` file and add the necessary redirects.

Now, whichever path you followed to get here (delete/refactor), the rest is the same for both:
1. Close Visual Studio
2. Generate the project files by right clicking the `.uproject` file and selecting `Generate Visual Studio project files`.\
	Optionally, delete the `Binaries`, `DerivedDataCache` and `Intermediate` folders for a clean regeneration.

### 3.2 Error and exception handling

Unreal Engine does not support exceptions, even though the `try`/`catch` keywords are a C++ language
feature. UE instead uses [Asserts](https://docs.unrealengine.com/5.3/en-US/asserts-in-unreal-engine).
These asserts are more performant, as for example, `check`-asserts are only executed in production builds.
Using exceptions with Unreal Engine is considered bad practice.

### 3.3 C++ features and Blueprint support

Another thing to keep in mind is, that not all C++ language features have an equivalent counterpart in the
Blueprint-system. This is a design choice by Unreal Engine, as it was too difficult to implement full support
for such features for Blueprints, at least at the moment. Using them in C++ code while exposinge said features
to the Blueprint-system via macros like `UFUNCTION` or `UPROPERTY` will result in the project no longer
compiling and instead throwing errors when building. Sometimes even with very obscure error messages.
Sadly there is no offical list of in Blueprints unsupported features on the Unreal Engine documentation.
The only related information may be obtained by looking at what types are available for
[Blueprint Variables](https://docs.unrealengine.com/5.3/en-US/blueprint-variables-in-unreal-engine).

For example, the following constructs do not exist in Blueprints:
1. References (`&`) are not available for Blueprints. It even fails with quite the obscure error message:
	`Found '&' when expecting '*'.`, not even mentioning the missing support in Blueprints.
2. Some primitives are not supported. This seems to stem from legacy code of UE3, in which only `uint8`,
	`int32` and `float` were supported. All other numerical data types were only fully available in C++
	code. Using unsupported primitives at least fails with a helpful error message:
	"Type 'int8' is not supported by blueprint. (...)"
3. Nested/multidimensional arrays aren't supported either.
