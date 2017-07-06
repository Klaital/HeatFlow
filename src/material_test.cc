#include "Material.h"
#include "gtest/gtest.h"

// Tests MatrixFile

TEST(MaterialUnitTest, CopyConstructor) {
	HeatFlow::Material material;
	material.set_name("MaterialUnitTest Material1");
    material.set_density(50001.2);
    material.set_conductivity(101.5);

    HeatFlow::Material copied_material(material);
	EXPECT_EQ("MaterialUnitTest Material1", copied_material.get_name());
    EXPECT_EQ(50001.2, copied_material.get_density());
    EXPECT_EQ(101.5, copied_material.get_conductivity());
}
