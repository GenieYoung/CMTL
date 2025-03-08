#include "CMTL/geo2d/geo2d_point.h"
#include <vector>
#include <gtest/gtest.h>

typedef CMTL::geo2d::Point<int> PointI;
typedef CMTL::geo2d::Point<double> PointF;
typedef CMTL::geo2d::Point<mpq_class> PointR;

TEST(Point2Test, ConstructTest)
{
    PointI pi0(1);
    EXPECT_EQ(pi0.dimension(), 2);
    //EXPECT_DEATH({pi0[2];}, "index out of range");
    EXPECT_EQ(pi0.x(), 1);
    EXPECT_EQ(pi0.y(), 0);

    EXPECT_EQ(PointI::Origin.x(), 0);
    EXPECT_EQ(PointI::Origin.y(), 0);

    PointI pi1(PointI(1, -1));
    EXPECT_EQ(pi1.x(), 1);
    EXPECT_EQ(pi1.y(), -1);

    PointI pi2(PointF(-1.5, 1.5));
    EXPECT_EQ(pi2.x(), -1);
    EXPECT_EQ(pi2.y(), 1);
}

TEST(Point2Test, OperationTest)
{
    PointR pr0(mpq_class(1, 3), mpq_class(-2, 7));
    PointR pr1(mpq_class(3, 7), mpq_class(2, 9));
    EXPECT_EQ(pr0%pr1, mpq_class(260, 1323));
}

// void test1()
// {
//     PointF fp0;
//     std::cout << "constructor in derived : " << fp0 << std::endl;
//     PointF fp1(1);
//     std::cout << "constructor in derived : " << fp1 << std::endl;
//     PointF fp2(2, 3);
//     std::cout << "constructor in derived : " << fp2 << std::endl;
//     PointF fp3(mpq_class(4), mpq_class(5));
//     std::cout << "template constructor in base : " << fp3 << std::endl;
//     // PointF fp4(mpq_class(4)); // wrong
//     PointF fp5(fp0);
//     std::cout << "default copy constructor in base : " << fp5 << std::endl;
//     PointF fp6(PointR(6, 7));
//     std::cout << "template copy cast constructor in base : " << fp6 << std::endl;
//     PointF fp7;
//     fp7 = fp6;
//     std::cout << "assign constructor in base : " << fp7 << std::endl;
//     PointF fp8;
//     fp8 = PointR(4, 4);
//     std::cout << "assign cast constructor in base : " << fp8 << std::endl;
// }

// void test2()
// {
//     PointF origin;
//     PointF p(1);
//     PointF q(p);
//     std::cout << "origin :      " << CMTL::geo2d::Point<double>::Origin << std::endl;
//     std::cout << "origin :      " << origin << std::endl;
//     std::cout << "p :           " << p << std::endl;
//     std::cout << "q :           " << q << std::endl;
//     std::cout << "assign :      " << (p=q) << std::endl;
//     std::cout << "p add q :     " << (p+q) << std::endl;
//     std::cout << "p cross q :   " << (p%q) << std::endl;
//     std::cout << "p norm2 :     " << p.length_square() << std::endl;
//     std::cout << "p == q :      " << (p==q) << std::endl;

//     PointR r_origin(origin);
//     PointR rp(5, 6);
//     PointR rq(q);
//     PointR s = (rp = p);
//     std::cout << "rorigin :     " << r_origin << std::endl;
//     std::cout << "rp :          " << rp << std::endl;
//     std::cout << "rq :          " << rq << std::endl;
//     std::cout << "rp assign p : " << (p = rp) << std::endl;
// }

// int main()
// {
//     test1();
//     //test2();
// }