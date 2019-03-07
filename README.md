# IL2206 Embedded Systems Laboratory

This repository contains the source files needed to get started with the IL2206 lab. You need to acquire them in one of the following way:

 * download a `.zip` archive by clicking _Clone or download_ -> _Download ZIP_. 
 * create an own repository and attach a remote to this one as presented in the [instructions on the course home page](https://kth.instructure.com/courses/6446/pages/setting-up-a-git-repositorty). 

## Contents 

This repository is organized as follows:

 * `app` contains source files for the lab applications, grouped in subfolders by project. It also contains build automation scripts for helping with the lab tasks,
 * `bsp` is an empty folder which might contain the generated Board Support Packages for different configurations in case you are using our build scripts.
 * `hardware` contains files describing the pre-built hardware cores. It is also a convenient place to host your hardware platform project folder(s).

### Choosing a work style

Unless specifically stated, the instructions in the lab manuals do not impose what tools to use in order to write an application and deliver any specific task. In this sense you have two alternatives to choose from:

 * use (mainly) the Eclipse IDE provided by Altera with its associated GUI tools. In this case the work flow is documented in the [Nios2 Eclipse Tutorial](https://www.intel.com/content/dam/altera-www/global/en_US/pdfs/literature/tt/tt_my_first_nios_sw.pdf) and you mainly need only the source files, which can be copied and included in your IDE projects. Thus you will be interested ***only** in the following files, ignoring the rest:
   - the source files (`.c`, `.h` or `.s`) found in `app/<project>/src/`
   - the pre-built hardware files found in `hardware/<your-board>/`
 * use your favorite code editor and use CLI tools for performing the tasks. In this case we have provided a bunch of automation scripts which can be used "as-is" or as inspiration for your own automation flow. We recommend studying their code and referring to the [Embedded Design Handbook, Chapter 4](https://www.altera.com/en_US/pdfs/literature/hb/nios2/edh_ed51004.pdf) for documentation on each command called. You can also go through this [Nios2 CLI tutorial](https://www.intel.com/content/dam/altera-www/global/en_US/pdfs/literature/hb/nios2/n2sw_nii52014.pdf), but with special care since it is outdated (it uses obsolete files and paths).

Although the GUI tools offer an attractive visual experience, _we strongly recommend_ using specialized code editors (e.g. emacs) and automation scripts (bash, make, Tcl, etc.). Often GUIs hide their commands, limiting the possibility to understand what is happening "behind the scene" and to customize your operations. Once properly understood and programmed, scripts offer a much faster and reproducible design process than "clicking around". Even if you have never worked with bash/Linux/CLI tools before, the provided files + Altera manuals should be enough to quickly get started, all you need more is willingness. 

## Using the prodvided automation scripts

As mentioned, apart from source files, this repository contains scripts which can be useful to quickly get started and should work "out-of-the-box" on the VM environment. There are two "flavors" of scripts, and you can chose one and stick with it:

### Bash scripts

We recommend using these scripts if you feel you are a beginner, since they are more humanly-readable. [GNU Bash](https://www.gnu.org/software/bash/) is a Linux shell used in the Ubuntu distribution of the VM. The scripts interpreted by this shell can be found in each project folder under `app`, usually called `run.sh` and consist mainly in calling a sequence of Nios II commands. 

Before your first usage you might need to modify some variables in the script. For example, open the script in the `hello_world` project in a code editor (here `emacs`):

        cd path/to/il2206-lab/app/hello_world
        emacs run.sh &

Study what the script does. By default, the path variables are poining to the DE2-35 pre-built hardware files. If you have been assigned with a DE2-115 board you need to commend/uncomment the proper lines (where commented lines start with `#`). For example you need to change this:

        # Paths for DE2-115 sources
        # CORE_FILE=../../hardware/DE2-115-pre-built/DE2_115_Nios2System.sopcinfo
        # SOF_FILE=../../hardware/DE2-115-pre-built/IL2206_DE2_115_Nios2.sof
        # JDI_FILE=../../hardware/DE2-115-pre-built/IL2206_DE2_115_Nios2.jdi

        # Paths for DE2-35 sources
        CORE_FILE=../../hardware/DE2-pre-built/DE2_Nios2System.sopcinfo
        SOF_FILE=../../hardware/DE2-pre-built/IL2206_DE2_Nios2.sof
        JDI_FILE=../../hardware/DE2-pre-built/IL2206_DE2_Nios2.jdi

into this:

        # Paths for DE2-115 sources
        CORE_FILE=../../hardware/DE2-115-pre-built/DE2_115_Nios2System.sopcinfo
        SOF_FILE=../../hardware/DE2-115-pre-built/IL2206_DE2_115_Nios2.sof
        JDI_FILE=../../hardware/DE2-115-pre-built/IL2206_DE2_115_Nios2.jdi

        # Paths for DE2-35 sources
        #CORE_FILE=../../hardware/DE2-pre-built/DE2_Nios2System.sopcinfo
        #SOF_FILE=../../hardware/DE2-pre-built/IL2206_DE2_Nios2.sof
        #JDI_FILE=../../hardware/DE2-pre-built/IL2206_DE2_Nios2.jdi

**Attention:** the scripts are calling commands only recognized from within the **Nios II Shell**, so in order to use them you need to open a **Nios II Shell** terminal and type in the commands:

        cd path/to/il2206-lab/app/your-project
        bash run.sh

To call execute a script without specifying an interpreter, you need to change the status of the script file to be executable, and than you can invoke simply with `./run.sh`:

        chmod +x run.sh
        ./run.sh

**Note:** if you run the scripts with the variables pointing to the wrong hardware files you might need to delete the generated BSP folder before running the script again:

        rm -rf path/to/il2206-lab/bsp/your-project-bsp

### Make scripts

[GNU Make](https://www.gnu.org/software/make/) is a more powerful build automation tool which handles the generation of artifacts based on dependency rules. We recommend using this script if you either are proficient in Linux tools or are willing to learn more about GNU Make. The Make scripts are found in each project folder and are mainly performing the same operations as their Bash counterparts, but separated as multiple _target rules_. 

The Make scripts are organized as follows:

* one global script found at `il2206-lab/app/Makefile.in` defining parameterized rules for all projects.
* a `Makefile` for each project which sets project-specific variables and import all the rules from `Makefile.in`, thus instatiating those rules. 

Before you start using the scripts, you need to check them, and at minimum modify the variables pointing to the hardware files accordingly, as suggested in the [Bash scripts](#bash-scripts) section.

        cd path/to/il2206-lab/app/your-project
        emacs Makefile &

A Make script can be invoked using the following commad from a project root (only from within a **Nios II Shell**):

        make [COMMAND]

where each available `[COMMAND]` is printed by calling `make help`.

**Note:** although the Altera documentation advises against using own `Makefile`s due to possible clashes with their own generated scripts, we have taken the precautions necessary to avoid these clashes and have provided the example `Makefile`s mainly for didactic purpose (i.e they are more readable than the ones generated by Nios tools).

## Using Git for code versioning

Make sure you make use of [`.gitignore`](https://www.atlassian.com/git/tutorials/saving-changes/gitignore) files so that you do not commit (unnecessary) generated files. You should only commit source files (e.g. `.c`, `.h`, `.s`, `.qsys`, `.qsf`, `.vhd`, `.v`, etc.) or your scripts (`.sh`, `Makefile`, etc.). Follow the hints from the [instructions on the course home page](https://kth.instructure.com/courses/6446/pages/setting-up-a-git-repositorty) on the basics of the Git workflow, as well as the documentation referenced there for more advanced topics such as branching and merging.


