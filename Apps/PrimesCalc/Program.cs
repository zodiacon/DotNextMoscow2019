using Calculators;
using System;

namespace PrimesCalc {
	static class Program {
		static void Main(string[] args) {
			Console.WriteLine("Calculating primes...");

            int first = 3, last = 100;

			if (args.Length > 1) {
				int.TryParse(args[0], out first);
				int.TryParse(args[1], out last);
			}

			var calc = new PrimesCalculator();

			foreach (int n in calc.Calculate(first, last)) {
				if (Console.KeyAvailable && Console.ReadKey().Key == ConsoleKey.Q)
					break;
				Console.WriteLine(n);
			}
		}
	}
}
