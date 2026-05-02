#include <iostream>
using namespace std;

template <typename T>
T celsiusToFahrenheit(T celsius) {
    return (celsius * 9.0 / 5.0) + 32;
}

template <typename T>
T celsiusToKelvin(T celsius) {
    return celsius + 273.15;
}

template <typename T>
T fahrenheitToCelsius(T fahrenheit) {
    return (fahrenheit - 32) * 5.0 / 9.0;
}

template <typename T>
void displayConversions(T inputCelsius) {
    cout << "=== Temperature Converter ===" << endl;
    cout << "Input (Celsius)     : " << inputCelsius << " C" << endl;
    cout << "To Fahrenheit       : " << celsiusToFahrenheit(inputCelsius) << " F" << endl;
    cout << "To Kelvin           : " << celsiusToKelvin(inputCelsius) << " K" << endl;

    T fahr = celsiusToFahrenheit(inputCelsius);
    cout << "\nBack to Celsius     : " << fahrenheitToCelsius(fahr) << " C" << endl;
}

int main() {
    cout << "--- Using int ---" << endl;
    displayConversions(100);   // Boiling point

    cout << "\n--- Using double ---" << endl;
    displayConversions(36.6);  // Human body temperature

    cout << "\n--- Using float ---" << endl;
    displayConversions(-40.0f); // Point where C and F are equal

    return 0;
}
