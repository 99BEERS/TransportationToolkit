# Transportation Engineering Toolkit

A Windows Forms desktop application for common transportation engineering calculations.

Implemented calculators:

- Horizontal curve geometry
- Symmetric vertical curves
- Superelevation

The remaining tabs are placeholders for sight distance, coordinate geometry, quantities, CSV import/export, and reports.

## Build and run

Open `TransportationToolkit.sln` in Visual Studio 2022, or run:

```powershell
dotnet run --project WinFormsPort\TransportationToolkit.csproj
```

The original native C++ source remains in the repository for reference. The solution now starts the .NET 8 Windows Forms application.

## License

MIT License

Copyright (c) 2026 Dominique Gladeau

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.