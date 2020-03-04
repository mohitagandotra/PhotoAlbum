# PhotoAlbum
PhotoAlbum App pulling data using RestAPI

## Screenshots
<img src="images/home_page.png" alt="Home page" width="300" height="300"> <img src="images/users_page.png" alt="Users page" width="300" height="300">

# Build instructions
## Dependencies
C++ 14, Qt 5.14, QMake

## Instructions
* Create build directory 'build'
* cd build
* qmake ../src/PhotoAlbum.pro
* make (use -j4 where 4 is number of parallel jobs)

Once the make tool finishes, the application binary should be available in the 'build' directory. for Example in case of macOS the app package name shall be PhotAlbum.app


# Unit tests
## Dependencies
Google test  [Download](https://github.com/google/googletest/archive/release-1.10.0.zip)
Qt 5.14, QML, QMake

## Instructions
* Extract the 'googletest' sources in the parent directory of 'PhotoAlbum'. i.e 'PhotoAlbum' and 'googletest' directories should be sibilings.
* Create build directory 'build-tests'
* cd build-tests
* qmake ../tests/unit_tests.pro
* make (use -j4 where 4 is number of parallel jobs)

Once the make tool finishes, run the binary "unit_tests"

# Class Diagram
![Class diagram](images/class_diagram.png)

