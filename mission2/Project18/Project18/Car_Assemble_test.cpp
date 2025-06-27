#include "gmock/gmock.h"

#include "Car_Assemble_View.h"
#include "Car_Assemble_Producer.h"

TEST(CarTest, DisplayViewTest)
{
	int stack[NUM_TOTAL_STACK];
	CarAssembleView carView(stack);

	EXPECT_NO_THROW(carView.displayView(CarType_Q));
	EXPECT_NO_THROW(carView.displayView(Engine_Q));
	EXPECT_NO_THROW(carView.displayView(brakeSystem_Q));
	EXPECT_NO_THROW(carView.displayView(SteeringSystem_Q));
	EXPECT_NO_THROW(carView.displayView(Run_Test));
}

TEST(CarTest, CarTypeBuildTest)
{
	Car::GetInstance().Build();
	CarEngine::GetInstance().Build();
	Brake::GetInstance().Build();
	Steering::GetInstance().Build();

	EXPECT_EQ(Car::GetInstance().GetTotalType(), NUM_TOTAL_CAR_TYPE);
	EXPECT_EQ(CarEngine::GetInstance().GetTotalType(), NUM_TOTAL_ENGINE_TYPE);
	EXPECT_EQ(Brake::GetInstance().GetTotalType(), NUM_TOTAL_BRAKE_SYSTEM_TYPE);
	EXPECT_EQ(Steering::GetInstance().GetTotalType(), NUM_TOTAL_STEERING_SYSTEM_TYPE);

}

TEST(CarTest, TypeNameTest)
{
	EXPECT_EQ(Car::GetInstance().GetTypeName(1), "SEDAN");
	EXPECT_EQ(CarEngine::GetInstance().GetTypeName(1), "GM");
	EXPECT_EQ(Brake::GetInstance().GetTypeName(1), "MANDO");
	EXPECT_EQ(Steering::GetInstance().GetTypeName(1), "BOSCH_S");
}

TEST(CarTest, CarAddTest)
{
	Car::GetInstance().AddType("NewCar");
	const int lastType = NUM_TOTAL_CAR_TYPE + 1;

	EXPECT_EQ(Car::GetInstance().GetTotalType(), lastType);
	EXPECT_EQ(Car::GetInstance().GetTypeName(lastType), "NewCar");
}

TEST(CarTest, EngineAddTest)
{
	CarEngine::GetInstance().AddType("NewEngine");
	const int lastType = NUM_TOTAL_ENGINE_TYPE + 1;

	EXPECT_EQ(CarEngine::GetInstance().GetTotalType(), lastType);
	EXPECT_EQ(CarEngine::GetInstance().GetTypeName(lastType), "NewEngine");
}

TEST(CarTest, BrakeAddTest)
{
	Brake::GetInstance().AddType("NewBrake");
	const int lastType = NUM_TOTAL_BRAKE_SYSTEM_TYPE + 1;

	EXPECT_EQ(Brake::GetInstance().GetTotalType(), lastType);
	EXPECT_EQ(Brake::GetInstance().GetTypeName(lastType), "NewBrake");
}

TEST(CarTest, SteeringAddTest)
{
	Steering::GetInstance().AddType("NewSteering");
	const int lastType = NUM_TOTAL_STEERING_SYSTEM_TYPE + 1;

	EXPECT_EQ(Steering::GetInstance().GetTotalType(), lastType);
	EXPECT_EQ(Steering::GetInstance().GetTypeName(lastType), "NewSteering");
}

TEST(CarTest, ProducerRunTest_CarRunnable)
{
	int stack[NUM_TOTAL_STACK];

	stack[0] = 1;
	stack[1] = 1;
	stack[2] = 1;
	stack[3] = 1;

;	CarAssembleProducter carProducer(stack);

	EXPECT_TRUE(carProducer.runProducedCar());
}

TEST(CarTest, ProducerRunTest_CarBroken)
{
	int stack[NUM_TOTAL_STACK];

	stack[0] = 1;
	stack[1] = 4;
	stack[2] = 1;
	stack[3] = 1;

	CarAssembleProducter carProducer(stack);

	EXPECT_FALSE(carProducer.runProducedCar());
}

TEST(CarTest, ProducerRunTest_CarDiabled)
{
	int stack[NUM_TOTAL_STACK];

	stack[0] = 1;
	stack[1] = 3;
	stack[2] = 2;
	stack[3] = 1;

	CarAssembleProducter carProducer(stack);

	EXPECT_FALSE(carProducer.runProducedCar());
}

TEST(CarTest, ProducerTest_CarRunnable)
{
	int stack[NUM_TOTAL_STACK];

	stack[0] = 1;
	stack[1] = 1;
	stack[2] = 1;
	stack[3] = 1;

	CarAssembleProducter carProducer(stack);

	EXPECT_TRUE(carProducer.testProducedCar());
}

TEST(CarTest, ProducerTest_CarDisable)
{
	int stack[NUM_TOTAL_STACK];

	stack[0] = 1;
	stack[1] = 3;
	stack[2] = 2;
	stack[3] = 1;

	CarAssembleProducter carProducer(stack);

	EXPECT_FALSE(carProducer.testProducedCar());
}