// Is Prime Number
// https://www.geeksforgeeks.org/c-program-to-check-prime-number/

#include <cstring>
#include <iostream>

bool isprime(uint64_t n, uint64_t* m_ptr)
{
  *m_ptr = 0;

  // Corner case
  if (n <= 1)
  {
    return false;
  }

  // Check from 2 to n-1
  for (uint64_t i = 2; i <= n / 2; i++)
  {
    if (n % i == 0)
    {
      *m_ptr = i;
      return false;
    }
  }

  return true;
}

int run_ut()
{
  std::cout << "Running Unit Tests..." << std::endl;

  int ret = 0;

  const uint64_t PN[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
                         47, 53, 59};

  const size_t N = sizeof(PN) / sizeof(PN[0]);

  uint64_t max = PN[N-1];

  uint64_t dummy = 0;

  for (uint64_t x = 2; x <= max; x++)
  {
  
    bool actual = isprime(x, &dummy);
    
    bool expected = false;
    for (int j = 0; j < N; j++)
    {
      if (x == PN[j])
      {
        expected = true;
        break;
      }
    }

    if (actual != expected)
    {      
      ret = 1;
      std::cout << "x=" << x << " actual=" << actual << " expected=" << expected << std::endl;
      break;
    }   
  }

  return ret;
}

int main(int argc, char* argv[])
{ 
  std::cout << "Hello!" << std::endl;

  for (int i = 0; i < argc; i++)
  {
    std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
  }  

  if ((argc > 1) && (std::strcmp(argv[1], "--run-ut") == 0))
  {
    return run_ut();
  }

  if ((argc > 1))
  {
    uint64_t x = 0;
    uint64_t m = 0;

    sscanf(argv[1], "%lud", &x);

    bool p = isprime(x, &m);

    std::cout << "isprime(" << x <<  ")=" << p << " m=" << m << std::endl;
  }
  
  return 0;
}
