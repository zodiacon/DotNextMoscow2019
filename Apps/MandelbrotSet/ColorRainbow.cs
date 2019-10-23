using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Xml.Linq;

namespace AsyncMandelbrot {
	class GradientGenerator {
		public double PhaseRed { get; set; }
		public double PhaseBlue { get; set; }
		public double PhaseGreen { get; set; }

		public double FreqRed { get; set; }
		public double FreqGreen { get; set; }
		public double FreqBlue { get; set; }

		public double MaxAngle { get; set; }

		public Color[] GenerateColors(int number) {
			var colors = new List<Color>(number);
			double step = MaxAngle / number;
			for(int i = 0; i < number; ++i) {
				var r = (Math.Sin(FreqRed * i * step + PhaseRed) + 1) * .5;
				var g = (Math.Sin(FreqGreen * i * step + PhaseGreen) + 1) * .5;
				var b = (Math.Sin(FreqBlue * i * step + PhaseBlue) + 1) * .5;
				colors.Add(Color.FromRgb((byte)(r * 255), (byte)(g * 255), (byte)(b * 255)));
			}
			return colors.ToArray();
		}

		public GradientGenerator() {
			FreqRed = FreqBlue = FreqGreen = 1;
			MaxAngle = Math.PI * 2;
		}
	}

	static class ColorGradientPersist {
		public static GradientGenerator Read(Stream stm) {
			var xml = XElement.Load(stm);
			return new GradientGenerator {
				FreqRed = (double)xml.Attribute("FreqRed"),
				FreqGreen = (double)xml.Attribute("FreqGreen"),
				FreqBlue = (double)xml.Attribute("FreqBlue"),
				PhaseRed = (double)xml.Attribute("PhaseRed"),
				PhaseGreen = (double)xml.Attribute("PhaseGreen"),
				PhaseBlue = (double)xml.Attribute("PhaseBlue"),
				MaxAngle = (double)xml.Attribute("MaxAngle"),
			};
		}

		public static void Write(GradientGenerator generator, Stream stm) {
			var xml = new XElement("Gradient",
			new XAttribute("FreqRed", generator.FreqRed),
			new XAttribute("FreqGreen", generator.FreqGreen),
			new XAttribute("FreqBlue", generator.FreqBlue),
			new XAttribute("PhaseRed", generator.PhaseRed),
			new XAttribute("PhaseGreen", generator.PhaseGreen),
			new XAttribute("PhaseBlue", generator.PhaseBlue),
			new XAttribute("MaxAngle", generator.MaxAngle));
			xml.Save(stm);

		}
	}
	static class Extensions {
		public static int ToInt(this Color color) {
			return (color.A << 24) | (color.B << 16) | (color.G << 8) | color.R;
		}
	}
}
