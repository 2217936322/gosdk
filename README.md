### Project isn't one of my priorities anymore, it has pieces of code that could be significantly improved, instead of advancements done on it by me, expect a new release of a different base. Kindest regards.

# gosdk
gosdk is a CS:GO SDK that is currently in development, written in C++17 standard, that empowers users to write CS:GO cheats.

# licensing
gosdk is licensed under the GNU v3 license, to find out more read [this](https://github.com/cristeigabriel/gosdk/blob/master/LICENSE) page.

# information
The formatting method for gosdk is a custom clang-format config that is often either recognized by Visual Studio (tested only on VS19) or usable throughout the CLI by installing a specific binary for it and running the command "clang-format -i (place).(format)"

# contribution guidelines
To contribute to gosdk, you must respect [these](http://web.mst.edu/~cpp/common/hungarian.html) Hungarian notation guidelines, and your code must be written in Pascal Case, if you implement code that isn't yours, it's recommended and asked that you source and credit the creator.

Hungarian notation is to be ignored on classes/structures that explicitly hold VFuncs/general game structures. Hungarian notation is to also be ignored in the Entity/Player header file and interface files.

We recommend you make enums that you add inherit a type. 

Use [CppTripleSlash](https://marketplace.visualstudio.com/items?itemName=tcbhat.CppTripleSlash-xmldoccommentsforc) to add documentation to your code [if you use Visual Studio 2019], or else, if you cannot, consider writing it by hand or asking someone to contribute to your commit by documenting it. (I, @cristeigabriel, will personally take that job if required)

# features
gosdk currently comes with the interfaces:
- IConsole
- IClient
- IClientMode
- IGlobalVars
- IEntityList
- IEngineClient
- IDebugOverlay
- IConsole
- ISurface
- IInputSystem
- IPanel
- IDevice pointing to Steam Overlay

and the hooks for:
- sv_cheats
- cl_grenadepreview
- CreateMove
- FrameStageNotify
- LockCursor
- PaintTraverse
- Present
- Reset
- WndProc

and the features:
- Bunny Hop
- No Duck Delay
- Box ESP
- Snaplines ESP
- Name ESP

alongside all of those, gosdk also supports:
- CMake (exceptions for pragma usage)
- VS Solutioning System

# faq
- Q: how do I fix pragma usage to use this alongside CMake?

- A: make use of CMake's handlers and for that matter you can make a .phx file that will handle all external libraries that cannot simply be put without requiring some sort of library inclusion

#

- Q: a function is now outdated and the repository is not yet updated, how should I proceed?

- A: refer to hazedumper, [this](https://github.com/frk1/hazedumper/blob/master/config.json) is the config file, and it has patterns to every function that is dumped, then [this](https://github.com/frk1/hazedumper/blob/master/csgo.hpp) contains the offsets and/or indexes, and a netvar dump.

#

- Q: when exactly will Linux support will be added?

- A: when I feel like doing it, in all honesty

#

- Q: when will a menu framework be implemented?

- A: when I or @otvv feel like implementing one.

#

Got any other questions? contact @cristeigabriel.

# why should I use this?
gosdk is aimed towards every developer by being intuitive and trying to reach a good performance in a compact codebase. Besides this, gosdk is also made to compile in very good times by being built around header usage. This, in the long run, assures less time spent on compiling. This can slow down rebuilds, but that is not considered a casual occourence.

# to-do
- Add a menu framework
- Linux support (This Summer)
- General code overlook to maintain consistency and clean-ness (Priority)
- Make rendering specific features work on a global render device object and make alias handlers [that means, some small changes to the render engine, unnoticeable]

# credits
Credits for gosdk go to:
- DucaRii - math utilities
- ReignN - VMT hooking class [modified], pattern scanning
- every gosdk contributor
