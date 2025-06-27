#ifdef _DEBUG

#include "gmock/gmock.h"
int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include "Car_Assemble_View.h"
#include "Car_Assemble_Producer.h"

int main()
{
    int stack[NUM_TOTAL_STACK];
    CarAssembleView carView(stack);
	CarAssembleProducter carProducer(stack);

    while (true)
    {
		static int step = CarType_Q;
        carView.displayView(step);

        int answer = carView.getUserInput(step);
        if (answer == INVALID_INPUT)
            continue;

        if (step == Run_Test)
        {
			carProducer.handleSelection(&step, answer);
        }
        else
        {
            carView.handleSelection(&step, answer);
        }
    }
}
#endif
