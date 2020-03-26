# Nanos-XiTAO #
Nanos-XiTAO is an integration repostiory that showcases interoperability between the XiTAO and Nanos runtime libraries (OmpSs backend). 

## Dependencies ##
1. The XiTAO runtime library, which can be found at https://github.com/mpericas/xitao.git
2. Nanos6 runtime for OmpSs-2 (tested with version 2.3.2) https://github.com/bsc-pm/nanos6.git
3. gcc/g++ version >= v7.5.0 
4. To enable testing, cblas compliant API such as cblas-lapack (e.g., http://www.netlib.org/lapack/#_lapack_version_3_9_0_2)

## Building the integration example ##
A makefile sample is provided in ```makefile.inc.sample```.
```bash
make nanos_xitao
```

## Running the batch tiled dense matrix multiplication example ##
```bash
make run
```

## ACKNOWLEDGEMENT ##
This work has been supported by EU H2020 ICT project LEGaTO, contract #780681.

