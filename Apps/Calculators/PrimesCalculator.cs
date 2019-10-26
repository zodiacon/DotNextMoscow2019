using System;
using System.Collections.Generic;

namespace Calculators {
	public sealed class PrimesCalculator {
		public IEnumerable<int> Calculate(int first, int last) {
			for (int i = first; i <= last; i++)
				if (IsPrime(i))
					yield return i;
		}

		static bool IsPrime(int n) {
			int limit = (int)Math.Sqrt(n);
			for (int i = 2; i <= limit; i++)
				if (n % i == 0)
					return false;
			return true;
		}
	}
}
