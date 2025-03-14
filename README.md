# PSU_ECE_RISC-V_ISA_Sim</br>
Simple RISC-V ISA Simulator; ECE 486/586 Winter 2025 Final Project</br>

[Test Plan Document](https://docs.google.com/document/d/1qdggXcx8wm82OrkbPRNxwOngLviSx2OqcZfvKck5cYE/edit?usp=sharing) </br>
```
To build use:

make main

Compile time argument flags.

-DVERBOSE -- Enable verbose output.
-DSTEP -- Enable key press instruction stepping.
-DDEBUG -- Enable debug output and define VEBOSE

Example:

$ make main EXTRA_CFLAGS="-DSTEP -DDEBUG"

Run time argument flags.
Default values are assumed when argument is absent.

-f <input file path> 
-s <stack Address> -- Starting stack address(Default = 65535)
-a <starting address> -- Word address(Default = 0)
-ft <input file type>  -- 0 = seqential index, -ft 1 = word address index(Default = 0)
-sp <input file spaces> -- The number of spaces folling the colon(Default = 2)

Example:

$ ./<app name> -f ./test_input.dat -s 65535 -a 0 
```

![Alt text](docs/main_map.png)
