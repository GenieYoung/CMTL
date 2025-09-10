CMTL(Computational Mathematics Tool Library)

Currently includes some geometric data structures and geometric algorithms, such as geometry shape, half-edge data structure. 
Geometry section is a template-based and header-only library, that you just need to include to use

for example:

lawson_flip_test.cpp
```

#include "CMTL/algorithm/lawson_flip.h"
#include "CMTL/io/surface_mesh/read_obj.h"
#include "CMTL/io/surface_mesh/write_obj.h"

typedef CMTL::geo2d::SurfaceMesh<double> SurfaceMesh;

int main()
{
    SurfaceMesh sm;
    CMTL::io::read_obj(sm, "leaf.obj");
    CMTL::io::write_obj(sm, "before_lawson_flip.obj");
    CMTL::algorithm::lawson_flip(sm);
    CMTL::io::write_obj(sm, "after_lawson_flip.obj");
}

```
compile it using the following command

`
g++ lawson_flip_test.cpp -o lawson_flip_test -I PATH/TO/SRC
`

if you use the rational number class, for example mpq_class, define USE_GMP and link the gmp

`
g++ lawson_flip_test.cpp -o lawson_flip_test -I PATH/TO/SRC -DUSE_GMP -lgmp -lgmpxx
`
