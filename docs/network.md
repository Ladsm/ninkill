# NINKILL Network & Internet Navigator

**Author:** Jack Wilder Dean (Head Software Engineer, Nuebine Inc.)  
**Date:** June 12, 1997  
**Subject:** Technical Specification for the SPP (Script++) Browser Engine

---

## System Overview

The **Network Internet Navigator** is a high-level terminal application designed to simulate a Wide Area Network (WAN) experience.  
Unlike standard software that requires manual installation, the Navigator uses a "Live-Load" system. 
It fetches data from remote addresses, renders it using the **SPP (Script++)** engine, and stores temporary traces in the VFS to maintain a low memory footprint.

## The Routing Table

The "Internet" in NINKILL is managed by a centralized **Route Table**.  
This is a `std::unordered_map` that acts as a localized DNS. It maps string-based URLs to specific C++ "Site Functions."

### Example Route Definition:

```cpp
{ H("www.jackwd.com"),  wwwJackwddotcom },
{ H("www.nuebine.com"), wwwNuebinedotcom },
{ H("www.mywebsitehere.com"), mywebsitesfunction },
```

---

## Script++ (SPP) Logic

SPP is a proprietary scripting language developed to simplify web design. In reality, SPP files are treated as "Temporary Binaries."

### The "Download" Process:

When a site is accessed, the engine uses the `mkfile` utility to write an .spp source file into the virtual `/tmp` directory. This allows advanced users to `cat` or `vi` the website's "source code" while the browser is active.

**SPP Source Example:**
```spp
#include "spp.hpp"
page 1 {
    w("Welcome to the Network.");
    l(2, "Next Page");
}
page 2{
    w("text here|nLine break");
    l(1, "back");
}
```

---

## Temporary Storage (/tmp)
To protect user privacy and system stability, all "Internet" data is stored in the `VNode* tmpDir`.

* **Persistence:** These files are transient.
* **The 10-Minute Wipe:** Per the original design, these traces are intended to be purged after the session ends.
* **Security:** Using `/tmp` prevents remote scripts from interfering with sensitive system nodes in `/bin` or `/etc`.

---

## Proxy Architecture
To prevent Arbitrary Code Execution (ACE), the Navigator does not connect directly to the host. It passes through a simulated Proxy Server.

```
                    .-----.         .-----------.    
   .----.     Fire  |  P  |         |---Server--+ - +
   |$>_ | - - - - - |--R--|         `-----+-----'   |
 __|____|__   Wall  |  O  | - - - - - - - |         |
|PC______--|        |--X--|         .-----+-----.   |
`-/.::::. \-'     +-+  Y  +-+       |--Display--|   |
 `--------'       | `-----' |       `-----+-----'   |
      |           |         |             |         |
      + - - - - - +         + - - - - - - + - - - - +
```

This proxy layer is what allows the Navigator to "Resolve Hosts" and handle redirects without exposing the local NINKILL kernel to external threats.

---

## Developer Notice
If you are developing a new site for the `nuedb.co.us` database, ensure your function returns the user to the `internet()` loop upon exit.  
Failure to do so will result in a stack overflow and a hard system reboot.

> **Note from Jack:**
> I built this to be free. Nuebine "acquired" it.
>
> — **Jack Wilder Dean**

## External Submission Portal
For developers without direct access to the `nuedb.co.us` terminal, Nuebine maintains a legacy web portal for SPP script submissions. 

**Portal Address:** [ladsm.neocities.org/getonnue](ladsm.neocities.org/getonnue)

> **Warning:** 
> Scripts submitted via the Neocities portal are subject to manual review by Jack Wilder Dean.  
> Unauthorized attempts will result in an immediate IP ban.

### (c) Nuebine Incorporated Network, 1998. All Rights Reserved.