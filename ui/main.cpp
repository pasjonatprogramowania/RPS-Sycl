#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
//////////TEST///////
#include <cstdlib>
#include <ctime>
//////////TEST///////
#include "Square.hpp"
class DrawableGrid {
public:
    virtual ~DrawableGrid() = default;
    virtual void draw(sf::RenderWindow& window) const = 0; // Czysta funkcja wirtualna wymuszająca implementację w klasach pochodnych
};
class SquareGrid : public DrawableGrid {
private:
    std::vector<std::vector<Square>> grid;
    float k_size;

public:
    SquareGrid(sf::RenderWindow& window, float size) : k_size(size) {
        buildGrid(window);
    }

    void buildGrid(sf::RenderWindow& window) {
        sf::Vector2u windowSize = window.getSize();
        float width = windowSize.x;
        float height = windowSize.y;
        float x_square = 0.0, y_square = 0.0;

        while (x_square <= width - k_size) {
            std::vector<Square> squares_rows;
            y_square = 0;
            while (y_square <= height - k_size) {
                squares_rows.emplace_back(x_square, y_square, "white", k_size);
                y_square += k_size;
            }
            grid.push_back(squares_rows);
            x_square += k_size;
        }
    }
    int countColor(const std::string& color) const {
        int count = 0;
        for (const auto& row : grid) {
            for (const auto& square : row) {
                if (square.getColor() == color) {
                    count++;
                }
            }
        }
        return count;
    }

bool canChangeColor(const std::string& currentColor, const std::string& newColor) {
    if (newColor == "white") return true; // Wszystko bije biały

    if (currentColor == "white") return true; // Z białego na cokolwiek

    if (currentColor == "blue" && newColor == "green") return true; // Niebieski bije zielony
    if (currentColor == "green" && newColor == "red") return true; // Zielony bije czerwony
    if (currentColor == "red" && newColor == "blue") return true; // Czerwony bije niebieski

    return false; // W pozostałych przypadkach zmiana koloru nie jest dozwolona
}

void changeSquareColor(int column, int row, const std::string& color) {
    if (grid.empty() || grid[0].empty()) return;  // Ochrona przed pustą siatką

    // Obliczenie prawidłowych indeksów przy użyciu modulo
    int wrappedColumn = (column + grid.size()) % grid.size();
    int wrappedRow = (row + grid[wrappedColumn].size()) % grid[wrappedColumn].size();

    // Pobranie obecnego koloru kwadratu
    std::string currentColor = grid[wrappedColumn][wrappedRow].getColor();

    // Sprawdzenie, czy zmiana koloru jest dozwolona
    if (canChangeColor(currentColor, color)) {
        grid[wrappedColumn][wrappedRow].setColor(color);
    }
}

int getWidth() const {
    return grid.empty() ? 0 : grid.size();
}

int getHeight() const {
    return grid.empty() ? 0 : grid[0].size();
}

int getTotalSquares() const {
    int total = 0;
    for (const auto& row : grid) {
        total += row.size();
    }
    return total;
}

    virtual void draw(sf::RenderWindow& window) const override {
        for (const auto& row : grid) {
            for (const auto& square : row) {
                square.draw(window);
            }
        }
    }
};
/////////////////////TEST///////////TEST////////TEST/////////////////
void setMaxFPS(sf::RenderWindow& window, unsigned int maxFPS) {
    window.setFramerateLimit(maxFPS);
}

class FPSCounter {
private:
    sf::Clock clock;
    float lastTime = 0.0f;
    int frameCount = 0;
    float fps = 0.0f;

public:
    // Wywoływane na początku każdej klatki
    void update() {
        frameCount++;
        float currentTime = clock.getElapsedTime().asSeconds();
        if (currentTime - lastTime >= 1.0f) { // Aktualizuj co sekundę
            fps = frameCount / (currentTime - lastTime);
            frameCount = 0;
            lastTime = currentTime;
        }
    }

    // Zwraca aktualne FPS
    float getFPS() const {
        return fps;
    }
};
/////////////////////TEST///////////TEST////////TEST/////////////////
int main() {
    sf::RenderWindow visualization_KPN(sf::VideoMode(960, 540), "Kamien Papier Nozyce");
/////////////////////TEST///////////TEST////////TEST/////////////////
    setMaxFPS(visualization_KPN, 120);
    FPSCounter fpsCounter;

/////////////////////TEST///////////TEST////////TEST/////////////////
    SquareGrid grid(visualization_KPN, 15.0f);
    std::cout<< "Ilosc kwadratow: " << grid.getTotalSquares() <<std::endl;
    std::cout << "Ilosc kwadratow po x: " << grid.getWidth() << std::endl;
    std::cout << "Ilosc kwadratow po y: " << grid.getHeight() << std::endl;

/////////////////////TEST///////////TEST////////TEST/////////////////
    int blueCount = 0;
    int redCount = 0;
    int greenCount = 0;
    int whiteCount = 0;

srand(time(nullptr));
        int randomNum = 0;
        int randomNum2 =0;
        int randomNum3 = 0;
        int randomNum4 =0;
        int randomNum5 = 0;
        int randomNum6 =0;

        int i=0,j=0;
/////////////////////TEST///////////TEST////////TEST/////////////////

    //grid.changeSquareColor(0, 0, "blue");
    while (visualization_KPN.isOpen()) {
        sf::Event event;
        while (visualization_KPN.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                visualization_KPN.close();
        }
/////////////////////TEST///////////TEST////////TEST/////////////////
fpsCounter.update();

        randomNum = rand()%grid.getWidth();
        randomNum2 = rand()%grid.getHeight();
        randomNum3 = rand()%grid.getWidth();
        randomNum4 = rand()%grid.getHeight();
        randomNum5 = rand()%grid.getWidth();
        randomNum6 = rand()%grid.getHeight();

                grid.changeSquareColor(randomNum, randomNum2, "blue");
                grid.changeSquareColor(randomNum3, randomNum4, "red");
                grid.changeSquareColor(randomNum5, randomNum6, "green");

                grid.changeSquareColor(i+1, i, "blue");
                grid.changeSquareColor(j+1, j, "red");
                grid.changeSquareColor(i+1, j, "green");
                grid.changeSquareColor(i, i+1, "blue");
                grid.changeSquareColor(j, j+1, "red");
                grid.changeSquareColor(i, j+1, "green");
                grid.changeSquareColor(i, i, "blue");
                grid.changeSquareColor(j, j, "red");
                grid.changeSquareColor(i, j, "green");

                i++;
                j--;

    blueCount = grid.countColor("blue");
        std::cout << "Ilosc niebieskich kwadratow: " << blueCount << std::endl;
    redCount = grid.countColor("red");
        std::cout << "Ilosc czerwonych kwadratow: " << redCount << std::endl;
    greenCount = grid.countColor("green");
        std::cout << "Ilosc zielonych kwadratow: " << greenCount << std::endl;
    whiteCount = grid.countColor("white");
        std::cout << "Ilosc bialych kwadratow: " << whiteCount << std::endl;
/////////////////////TEST///////////TEST////////TEST/////////////////


        visualization_KPN.clear(sf::Color::Black); // Czyszczenie okna na czarno

        // Rysowanie kwadratow
        grid.draw(visualization_KPN);

        visualization_KPN.display();
/////////////////////TEST///////////TEST////////TEST/////////////////

//std::cout << "Aktualne FPS: " << fpsCounter.getFPS() << std::endl;
/////////////////////TEST///////////TEST////////TEST/////////////////

    }

    return 0;
}
