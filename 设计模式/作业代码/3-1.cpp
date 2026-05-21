#include <iostream>
class Calculator
{
public:
    virtual double calculate(int a, int b) = 0;
    virtual ~Calculator(){};
};
class AddCalculator : public Calculator
{
    virtual double calculate(int a, int b)
    {
         return a + b;
        
    }
};
class SubCalculator : public Calculator
{
    virtual double calculate(int a, int b)
    {
         return a - b;
        
    }
};
class MulCalculator : public Calculator
{
    virtual double calculate(int a, int b)
    {
         return a * b;
        
    }
};
class DivCalculator : public Calculator
{
    virtual double calculate(int a, int b)
    {
         return a / (double)b;
        
    }
};
class CalculatorFactory
{
public:
    Calculator *getCalculator(char operation)
    {
         switch (operation)
        {
          case '+':
               return new AddCalculator();
               break;
          case '-':
               return new SubCalculator();
               break;
          case '*':
               return new MulCalculator();
               break;
          case '/':
               return new DivCalculator();
             
        }
        
    }
};
int main()
{
    Calculator *pCalculator = nullptr;
    CalculatorFactory *pCalculatorFactory = new CalculatorFactory();
    int a = 0, b = 0;
    char operation = 0;
    std::cin >> a >> operation >> b;
    pCalculator = pCalculatorFactory->getCalculator(operation);
    std::cout << pCalculator->calculate(a, b);
    delete pCalculator;
    delete pCalculatorFactory;
    return 0;
}