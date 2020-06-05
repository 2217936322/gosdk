# gosdk
gosdk is a CS:GO SDK that is currently in development, written in C++17 standard, that empowers users to write CS:GO cheats.

# licensing
gosdk is licensed under the GNU v3 license, and according to that, I, Cristei Gabriel-Marian, provide you the code as-is, and give you full freedom over the usage of it, but I will not take responsability for your usage of it. Please consider consulting the actual licensing terms by clicking on the "GPL v3.0" button that should be next to the contributors tab.

# information
The formatting method for gosdk is a custom clang-format config that is often either recognized by Visual Studio versions (tested only on VS19) or usable throughout the CLI by installing a specific binary for it and running the command "clang-format -i (place).(format)"

# contribution guidelines
To contribute to gosdk, you must respect [these](http://web.mst.edu/~cpp/common/hungarian.html) Hungarian notation guidelines, and your code must be written in Pascal Case, if you implement code that isn't yours, it's recommended and asked that you source and credit the creator.

Member and Hungarian notation is to be ignored on classes/structures that explicitly hold VFunctions/generally game structures (this excludes stuff like ClientClass as an example, but also as an example includes structures like ISurface). This is because, first, it improves readability for those very functions, and second, datatype is inherited from auto. This rule excludes the Entity/Player header file.

We recommend you make enums that you add inherit a type. 

Use [CppTripleSlash](https://marketplace.visualstudio.com/items?itemName=tcbhat.CppTripleSlash-xmldoccommentsforc) to add documentation to your code [if you use Visual Studio 2019], or else, if you cannot, consider writing it by hand or asking someone to contribute to your commit by documenting it. (I, @cristeigabriel, will personally take that job if required)

# features
gosdk currently comes with the IConsole interface, ISurface interface, IInputSystem interface, IPanel interface, IBaseClientDLL for Client interface, ClientMode interface, IEngineClient interface, IEntityList interface, IGlobalVars interface, IDebugOverlay interface, a basic Surface wrapper, D3D rendering devices (Present [hooked], Reset [hooked]) alongside a D3D rendering engine, a Netvar scanner, a VMT hooking class, sv_cheats Bypass (hooked), Grenade Trajectory (convar, hooked), Lock Cursor [currently while Insert is held] (hooked), Paint Traverse [hooked], Create Move [hooked], WindowProcessHook, ability to do basic rendering, a console with logging, basic error handling, math utilities, various easing functions and utilities which include a color handler and a config system, memory functions, bunny hop and no duck delay through bitflag easing, Box ESP, Snaplines ESP and Name ESP. These are not final and are to be updated.

Besides the cheating functions, gosdk comes with compability for every IDE, based on the secondary way of project solution generation, by adding a ready-to-use CMake config to the repository. If you use the CMake solution method, you can delete any VS generated file in favor of those provided, or if you use the VS solution method, you can just delete the CMake related ones.

# why should I use this?
gosdk is aimed towards every developer by being very intuitive and trying to reach the best performance in a compact codebase. Besides performance, gosdk has very fast compilation times because it is built to revolve around header usage. As a disclaimer, header-only usage can slow down compilation times, but that will actually happen only on complete rebuilds and/or first builds, but it will save a lot of time in the future.

# to-do
- Add a menu framework

# credits
Credits for gosdk go to places where I take inspiration from, and that would be:
- @DucaRii for csgo_modest [his project helped me with the math utilities].
- @ReigN [unknowncheats.me] for their SDK that I have got the VMT Hooking class from, which was a total time saver, despite some nitpickable issues that are not occouring within this project.
- A few UnknownCheats users for functions that were already posted there to make my life easier.
- Every supposive contributor.
