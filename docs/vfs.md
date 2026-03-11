# NINKILL VFS System Documentation

**Author:** Hoien Shaun Dow (Nuebine Inc. Systems Division)  
**Date:** March 24, 1998  
**Subject:** Technical Overview of the NINKILL RAM-Disk

---

## What is a VFS?
A **VFS** (Virtual File System) is the software layer that allows the NINKILL kernel to interact with files and folders in memory.  
In NINKILL OS 1.3, this acts as our primary **RAM-Disk**.  
Because the system is designed to be lightweight, we do not use a physical disk driver for standard operations; instead, we build the entire world as a recursive object tree.
## The Core Object: `VNode`
The building block of the entire system is the `VNode` struct.  
It is a "Fat Node" design, meaning a single structure handles files, directories, and executable binaries.
### Structure Definition
```cpp
struct VNode {
	std::string name;                                             // Node identifier (e.g. "bin")
	bool isDir;                                                   // Toggle: True = Directory, False = File
	std::string content;                                          // Raw text data (for files)
	bool isExec = false;                                          // Execution flag
	std::function<int(const std::vector<std::string>&)> execFunc; // Logic callback for "programs"
	VNode* parent = nullptr;                                      // Upward link (essential for 'cd ..')
	std::map<std::string, std::unique_ptr<VNode>> children;       // Downward links (Automatic Memory Management)
	bool locked = false;                                          // Security state (password protection)
	std::string passwordHash;                                     // Obfuscated Password
	VNode(std::string n, bool d, VNode* p = nullptr)
		:name(std::move(n)), isDir(d), parent(p) {}
};
```

## API Reference

### 1. Navigation & Pathing

*   **VNode* resolvePath(const std::string& path)**  
    The "GPS" of the engine. Converts a string (e.g., `../../bin/vi.exc`) into a pointer to a `VNode`.
    *   Handles absolute paths (starting with `/`).
    *   Handles relative paths (starting from `cwd`).
    *   Supports `..` (parent) and `.` (current) tokens.

*   **std::string cwdPath()**  
    Recursively walks up `parent` pointers from the `cwd` to build the full directory string displayed in the terminal prompt.

*   **void printTree(VNode* node)**  
    A recursive visualizer that prints an ASCII representation of the directory structure. If a node is `locked`, the tree will not display its children.

### 2. File & Directory Creation

*   **VNode* mkdirNode(VNode* parent, const std::string& name)**  
    Initializes a new directory node and attaches it to the parent's `children` map. Returns a raw pointer to the new node.

*   **VNode* mkfile(VNode* parent, const std::string& name, const std::string& txt)**  
    Initializes a new file node with the provided `content` (txt).

*   **void mkuserfiles(VNode* dir)**  
    A standard utility to generate a "Home" environment, creating `documents`, `downloads`, `audio`, `videos`, and `images` folders.  
Note: Implementation of this utility is currently suspended per nin.  
Originally intended for the 'Nuebine Interaction Manager' project (Cancelled Q3 1999).

### 3. Security & Access Control

*   std : : string hashPass(const std::string& s)
    Uses a standard hash to ensure passwords (like `passwd123`) are never stored in plain text within the RAM-disk.

*   **void lockDir(VNode* dir, const std::string& pass)**  
    Sets a directory to a `locked` state and stores the hashed version of the password.

*   **bool unlockDir(VNode* dir, const std::string& attempt)**  
    Validates a user's input against the stored hash. Returns `true` only if the attempt is correct.

### 4. Lifecycle Management

*   **void initFS()**  
    The "World Builder." Generates the default NINKILL environment at boot, including the `/bin` utilities, `/etc` config files, and `/home` user directories.

*   **void wipeFS()**  
    The emergency reset. Wipes the `root` children and rebuilds a minimal "Admin State" containing the `/priv` node and the `wallet.dat`.


## notice 1

```
The VDD (Virtual Dynamic Disk) must remain mounted at all times.
The spilling of forum logs into this disk is a known bug and should be ignored by all personnel.
 - Nin becker Fin
```

## notice 2

```
Use of this documentation for non program development means is prohibided and ilegel.
```

### (c)Nuebine Incorperated Network, 1998. All Rights Reserved