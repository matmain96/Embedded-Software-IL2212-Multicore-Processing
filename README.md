# IL2212 Embedded Systems Laboratory



## Contents 

This repository is organized as follows:

 * `app` contains source files for the lab applications, grouped in subfolders by project. It also contains build automation scripts for helping with the lab tasks,
 * `bsp` is an empty folder which might contain the generated Board Support Packages for different configurations in case you are using our build scripts.
 * `hardware` contains files describing the pre-built hardware cores. It is also a convenient place to host your hardware platform project folder(s).

## Objectives
The task of this project is to implement a concurrent data-flow application in different ways on a multiprocessor that is implemented on an FPGA. Students shall apply their knowledge from the lectures in order to derive an efficient implementation exploiting the parallelism provided by the architecture.

During this project students shall:

* identify the architecture of the multiprocessor analyzing the provided Altera design files;
* understand the model and the functionality of the data-flow application;
* get acquainted with collaborative development using the Git versioning system;
* implement the application
* on a single core using the real-time operating system MicroC/OS-II;
* on a single core without operating system;
* on the multiprocessor without operating system while satisfying design constraints on worst case throughput and memory footprint;
document the results of the project in a well-written report which will be assessed and used as support during lab examination.

## Application Specification
Your task for this lab project is to implement an image tracking algorithm which tracks a (given) moving "circle" pattern in a series of image frames for the purpose of further processing. You are supposed to implement this application on a (given) custom multi-processor hardware platform hosted on a DE2 FPGA, in three ways:

* on a single core, using the MicroC/OS-II
* on a single core, without OS
* on multiple cores, without OS
