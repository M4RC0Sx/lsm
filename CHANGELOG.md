# lsm - Changelog

## [1.2.0](https://github.com/M4RC0Sx/lsm/compare/v1.1.0...v1.2.0) (2022-11-20)


### Features

* added macros file for better handling ([a066d04](https://github.com/M4RC0Sx/lsm/commit/a066d04eb8c2461db1af17f6506ac9f450744837))
* **lsm_printer:** display icons based on file type, closes [#21](https://github.com/M4RC0Sx/lsm/issues/21) ([547fad5](https://github.com/M4RC0Sx/lsm/commit/547fad55f20a6c668e39fb131d14195407b009b9))

## [1.1.0](https://github.com/M4RC0Sx/lsm/compare/v1.0.0...v1.1.0) (2022-11-16)


### Features

* added -l option ([a21f47e](https://github.com/M4RC0Sx/lsm/commit/a21f47e512b756a9002f19dba45654843824e5ac))
* added -l option, closes [#17](https://github.com/M4RC0Sx/lsm/issues/17) ([46703b1](https://github.com/M4RC0Sx/lsm/commit/46703b159b2557462a49afb8714fa95ade9b1bf5))
* **lsm_file:** handle is_hidden and is_dot properties ([4046b96](https://github.com/M4RC0Sx/lsm/commit/4046b9692b322c60c9127bbf3d6dd18e79ba503c))
* **lsm_printer:** pretty display function for -l option, closes [#18](https://github.com/M4RC0Sx/lsm/issues/18) ([23b4895](https://github.com/M4RC0Sx/lsm/commit/23b4895cfb11d7a803af49fd98f1cf08d53e7db9))


### Bug Fixes

* **memory-leak:** free resources before exit_failure, closes [#16](https://github.com/M4RC0Sx/lsm/issues/16) ([cff3baf](https://github.com/M4RC0Sx/lsm/commit/cff3bafcf36746a71aef92cf5ac8d77a082b2407))

## 1.0.0 (2022-11-13)


### Features

* added dummy main file ([f60b0fe](https://github.com/M4RC0Sx/lsm/commit/f60b0fe0367d14bdb806627286134cd519b903b8))
* **arg-parsing:** added arg/opt parser and ability to specify target path, closes [#1](https://github.com/M4RC0Sx/lsm/issues/1) ([ad4df55](https://github.com/M4RC0Sx/lsm/commit/ad4df55a825d49205f0debc62a6a07e38ec4ede2))
* base functionallity, early implementation ([1f24085](https://github.com/M4RC0Sx/lsm/commit/1f240853820b6ef1fc99266e99602a333eb11297))
* **dot-files:** added option to include d. and .. ([0b8d532](https://github.com/M4RC0Sx/lsm/commit/0b8d53246e3ffac1e9d62d4debedad34c05af2a7))
* **error-handling:** check errors while opening target path ([3c64a73](https://github.com/M4RC0Sx/lsm/commit/3c64a73cc9fafd8327ed8f2d50540b0be3793ae4))
* handle dirs/paths as abstract data types ([465c115](https://github.com/M4RC0Sx/lsm/commit/465c1150dbb3995440889f340c1c506dba7c0de6))
* handle dirs/paths as abstract data types, closes [#7](https://github.com/M4RC0Sx/lsm/issues/7) ([aca667f](https://github.com/M4RC0Sx/lsm/commit/aca667f54549f61e67949f27848045f91271f9a8))
* **hidden-files:** do not display hidden files by default ([4f80031](https://github.com/M4RC0Sx/lsm/commit/4f80031b4defc9dcb6bc67dc27adf0d8a82360fd))
* **hidden-files:** handle -a argument ([24252ba](https://github.com/M4RC0Sx/lsm/commit/24252baf45c04e6fef7be7ec2da256c68c3bcd50))
* **lsm_dir:** create lsm_dir abstract data type ([9e8d649](https://github.com/M4RC0Sx/lsm/commit/9e8d64996dd8f3ae561303185478d2dd438e26e3))
* **lsm_dir:** directory reading function ([e996ff1](https://github.com/M4RC0Sx/lsm/commit/e996ff126f2c5eea3e9a8854127d30ae05a5aeb2))
* **lsm_dir:** do not read any file stat ([77daa65](https://github.com/M4RC0Sx/lsm/commit/77daa65dd6e10ffcd6db4054d7880d5839577d8f))
* **lsm_file:** handle files as abstract data types, closes [#8](https://github.com/M4RC0Sx/lsm/issues/8) ([9aa6f4e](https://github.com/M4RC0Sx/lsm/commit/9aa6f4e20bd5c4005076c22d9da02f11e2b5cb20))
* **lsm_file:** handled a bunch of stats, closes [#11](https://github.com/M4RC0Sx/lsm/issues/11) ([777e486](https://github.com/M4RC0Sx/lsm/commit/777e4862eadd42f0ff9820b5f5deda0e212a62f4))
* **path-handling:** set default path to . and allow multiple paths as arguments, closes [#6](https://github.com/M4RC0Sx/lsm/issues/6) ([e6c70be](https://github.com/M4RC0Sx/lsm/commit/e6c70bebc9bbdd602690ed44b74035a77e25ee42))


### Bug Fixes

* **release-workflow:** branches typo ([40d76cc](https://github.com/M4RC0Sx/lsm/commit/40d76cc93125c204ea9d18303a7afd47fbec19b6))
