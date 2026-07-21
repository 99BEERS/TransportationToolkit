using System.Globalization;

namespace TransportationToolkit;

public sealed class Form1 : Form
{
    private readonly Color navy = Color.FromArgb(20, 48, 72);
    private readonly Color blue = Color.FromArgb(24, 111, 176);

    public Form1()
    {
        Text = "Transportation Engineering Toolkit";
        MinimumSize = new Size(900, 620);
        Size = new Size(1080, 720);
        StartPosition = FormStartPosition.CenterScreen;
        BackColor = Color.FromArgb(244, 247, 249);
        Font = new Font("Segoe UI", 10F);

        var header = new Label { Text = "  TRANSPORTATION ENGINEERING TOOLKIT", Dock = DockStyle.Top,
            Height = 76, BackColor = navy, ForeColor = Color.White,
            Font = new Font("Segoe UI Semibold", 19F), TextAlign = ContentAlignment.MiddleLeft };
        var tabs = new TabControl { Dock = DockStyle.Fill, Padding = new Point(14, 7) };
        tabs.TabPages.Add(HorizontalPage());
        tabs.TabPages.Add(VerticalPage());
        tabs.TabPages.Add(SuperelevationPage());
        foreach (var title in new[] { "Sight Distance", "Coordinate Geometry", "Quantities", "CSV Import/Export", "Reports" })
            tabs.TabPages.Add(ComingSoon(title));
        Controls.Add(tabs);
        Controls.Add(header);
    }

    private TabPage HorizontalPage()
    {
        var radius = Input(); var delta = Input(); var output = Output();
        return Calculator("Horizontal Curve", "Circular curve geometry",
            new[] { ("Radius (m)", radius), ("Delta angle (degrees)", delta) }, output, () =>
        {
            if (!Positive(radius, "Radius", out var r) || !Range(delta, "Delta angle", 0, 180, out var d)) return;
            var angle = d / 2 * Math.PI / 180;
            var tangent = r * Math.Tan(angle);
            var curveLength = Math.PI * r * d / 180;
            var chord = 2 * r * Math.Sin(angle);
            var external = r * (1 / Math.Cos(angle) - 1);
            var middleOrdinate = r * (1 - Math.Cos(angle));

            output.Text = "FORMULAS AND SUBSTITUTION\r\n" +
                $"Half-angle = Δ/2 = {d:N3}°/2 = {d / 2:N3}° = {angle:N6} rad\r\n\r\n" +
                $"T = R tan(Δ/2)\r\n  = {r:N3} tan({d / 2:N3}°)\r\n  = {tangent:N3} m\r\n\r\n" +
                $"L = πRΔ/180\r\n  = π({r:N3})({d:N3})/180\r\n  = {curveLength:N3} m\r\n\r\n" +
                $"LC = 2R sin(Δ/2)\r\n  = 2({r:N3}) sin({d / 2:N3}°)\r\n  = {chord:N3} m\r\n\r\n" +
                $"E = R[sec(Δ/2) - 1]\r\n  = {r:N3}[1/cos({d / 2:N3}°) - 1]\r\n  = {external:N3} m\r\n\r\n" +
                $"M = R[1 - cos(Δ/2)]\r\n  = {r:N3}[1 - cos({d / 2:N3}°)]\r\n  = {middleOrdinate:N3} m";
        });
    }

    private TabPage VerticalPage()
    {
        var g1 = Input(); var g2 = Input(); var length = Input(); var pvi = Input(); var elevation = Input(); var output = Output();
        return Calculator("Vertical Curve", "Symmetric parabolic vertical curve",
            new[] { ("Incoming grade g1 (%)", g1), ("Outgoing grade g2 (%)", g2),
                ("Curve length L (m)", length), ("PVI station (m)", pvi), ("PVI elevation (m)", elevation) }, output, () =>
        {
            if (!Read(g1, "Incoming grade", out var aPct) || !Read(g2, "Outgoing grade", out var bPct) ||
                !Positive(length, "Curve length", out var l) || !Read(pvi, "PVI station", out var pviSta) ||
                !Read(elevation, "PVI elevation", out var pviElev)) return;
            var a = aPct / 100; var b = bPct / 100; var diff = b - a;
            var pvcSta = pviSta - l / 2; var pvtSta = pviSta + l / 2;
            var pvcElev = pviElev - a * l / 2; var pvtElev = pviElev + b * l / 2;
            output.Text = "FORMULAS AND SUBSTITUTION\r\n" +
                $"g1 = {aPct:N3}/100 = {a:N6}\r\ng2 = {bPct:N3}/100 = {b:N6}\r\n" +
                $"A = g2 - g1 = {b:N6} - ({a:N6}) = {diff:N6} ({bPct - aPct:N3}%)\r\n\r\n" +
                $"PVC station = PVI - L/2\r\n  = {pviSta:N3} - {l:N3}/2 = {pvcSta:N3} m\r\n\r\n" +
                $"PVT station = PVI + L/2\r\n  = {pviSta:N3} + {l:N3}/2 = {pvtSta:N3} m\r\n\r\n" +
                $"PVC elevation = PVI elevation - g1(L/2)\r\n  = {pviElev:N3} - ({a:N6})({l:N3}/2) = {pvcElev:N3} m\r\n\r\n" +
                $"PVT elevation = PVI elevation + g2(L/2)\r\n  = {pviElev:N3} + ({b:N6})({l:N3}/2) = {pvtElev:N3} m";
            if (Math.Abs(diff) > 0.0000001 && -a * l / diff is var distance && distance >= 0 && distance <= l)
            {
                var pointElev = pvcElev + a * distance + diff * distance * distance / (2 * l);
                output.Text += $"\r\n\r\n{(diff < 0 ? "HIGH POINT" : "LOW POINT")}\r\n" +
                    $"x = -g1L/A\r\n  = -({a:N6})({l:N3})/({diff:N6}) = {distance:N3} m from PVC\r\n" +
                    $"Station = {pvcSta:N3} + {distance:N3} = {pvcSta + distance:N3} m\r\n\r\n" +
                    $"Elevation = E(PVC) + g1x + Ax²/(2L)\r\n" +
                    $"  = {pvcElev:N3} + ({a:N6})({distance:N3}) + ({diff:N6})({distance:N3})²/[2({l:N3})]\r\n" +
                    $"  = {pointElev:N3} m";
            }
            else output.Text += "\r\n\r\nHIGH/LOW POINT CHECK\r\nNo high or low point occurs within the curve.";
        });
    }

    private TabPage SuperelevationPage()
    {
        var speed = Input(); var radius = Input(); var friction = Input(); var output = Output();
        return Calculator("Superelevation", "Estimate the required roadway cross slope",
            new[] { ("Design speed (km/h)", speed), ("Radius (m)", radius), ("Side friction factor", friction) }, output, () =>
        {
            if (!Positive(speed, "Design speed", out var s) || !Positive(radius, "Radius", out var r) ||
                !Read(friction, "Side friction factor", out var f)) return;
            var rate = s * s / (127 * r) - f;
            output.Text = "FORMULA AND SUBSTITUTION\r\n" +
                "e = V²/(127R) - f\r\n" +
                $"  = {s:N3}²/[127({r:N3})] - {f:N3}\r\n" +
                $"  = {s * s:N3}/{127 * r:N3} - {f:N3}\r\n" +
                $"  = {rate:N3}\r\n\r\n" +
                $"Superelevation = e × 100 = {rate:N3} × 100 = {rate * 100:N3}%";
        });
    }

    private TabPage Calculator(string title, string subtitle, (string label, TextBox input)[] fields, TextBox output, Action calculate)
    {
        var page = new TabPage(title) { BackColor = BackColor, Padding = new Padding(20) };
        var split = new TableLayoutPanel { Dock = DockStyle.Fill, ColumnCount = 2 };
        split.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 44)); split.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 56));
        var inputs = new TableLayoutPanel { Dock = DockStyle.Fill, AutoScroll = true, BackColor = Color.White, Padding = new Padding(24), Margin = new Padding(8) };
        inputs.Controls.Add(new Label { Text = title, AutoSize = true, Font = new Font("Segoe UI Semibold", 18F), ForeColor = navy });
        inputs.Controls.Add(new Label { Text = subtitle, AutoSize = true, ForeColor = Color.DimGray, Margin = new Padding(3, 0, 3, 10) });
        foreach (var field in fields) { inputs.Controls.Add(new Label { Text = field.label, AutoSize = true, Margin = new Padding(3, 10, 3, 3) }); inputs.Controls.Add(field.input); }
        var button = new Button { Text = "Calculate", Height = 42, BackColor = blue, ForeColor = Color.White,
            FlatStyle = FlatStyle.Flat, Margin = new Padding(3, 20, 3, 3), Dock = DockStyle.Top };
        button.FlatAppearance.BorderSize = 0; button.Click += (_, _) => calculate(); inputs.Controls.Add(button);
        var results = new Panel { Dock = DockStyle.Fill, BackColor = Color.White, Padding = new Padding(24), Margin = new Padding(8) };
        results.Controls.Add(output); results.Controls.Add(new Label { Text = "RESULTS", Dock = DockStyle.Top, Height = 45,
            Font = new Font("Segoe UI Semibold", 13F), ForeColor = navy });
        split.Controls.Add(inputs); split.Controls.Add(results); page.Controls.Add(split); return page;
    }

    private TabPage ComingSoon(string title)
    {
        var page = new TabPage(title) { BackColor = BackColor };
        page.Controls.Add(new Label { Text = $"{title}\r\n\r\nThis tool is ready for implementation.", Dock = DockStyle.Fill,
            TextAlign = ContentAlignment.MiddleCenter, Font = new Font("Segoe UI Semibold", 18F), ForeColor = navy }); return page;
    }

    private static TextBox Input() => new() { Width = 300, BorderStyle = BorderStyle.FixedSingle };
    private static TextBox Output() => new() { Dock = DockStyle.Fill, Multiline = true, ReadOnly = true,
        BorderStyle = BorderStyle.None, Font = new Font("Consolas", 11F), ScrollBars = ScrollBars.Vertical };
    private static bool Read(TextBox box, string name, out double value)
    {
        if (double.TryParse(box.Text, NumberStyles.Float, CultureInfo.CurrentCulture, out value)) return true;
        MessageBox.Show($"Enter a valid number for {name}.", "Invalid input", MessageBoxButtons.OK, MessageBoxIcon.Warning); box.Focus(); return false;
    }
    private static bool Positive(TextBox box, string name, out double value)
    {
        if (Read(box, name, out value) && value > 0) return true;
        if (double.IsFinite(value)) MessageBox.Show($"{name} must be greater than zero.", "Invalid input", MessageBoxButtons.OK, MessageBoxIcon.Warning); return false;
    }
    private static bool Range(TextBox box, string name, double min, double max, out double value)
    {
        if (Read(box, name, out value) && value > min && value < max) return true;
        if (double.IsFinite(value)) MessageBox.Show($"{name} must be between {min} and {max}.", "Invalid input", MessageBoxButtons.OK, MessageBoxIcon.Warning); return false;
    }
}
