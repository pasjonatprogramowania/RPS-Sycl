#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Square.hpp"

//Sta�e powinny by� zapisywane wielkimi literami, (konwencja programistyczna).
float k_size=50.0;//rozmiar kwadratu
//Zmie� nazw� na co� podobnego do getQuantityBy... Nazwa metody powinna jednoznacznie informowa�, co jest zwracane i wed�ug jakich parametr�w.
float k_quantity(sf::RenderWindow& window, float k_size) {
    sf::Vector2u windowSize = window.getSize();
    float width = windowSize.x;
    float height = windowSize.y;
    std::cout << width << " " << height << std::endl;
    float quantity=(width*height)/(k_size*k_size);

    // Zwracanie stosunku szerokosci do wysoko�ci jako float
    return quantity;
}
//Nazwa metody nie okre�la jednoznacznie, co robi funkcja ani jakie parametry przyjmuje
std::vector<std::vector<Square>> k_maker(sf::RenderWindow& window, float size) {
    sf::Vector2u windowSize = window.getSize();
    float width = windowSize.x;
    float height = windowSize.y;
    float x_square = 0.0, y_square = 0.0;
    std::vector<std::vector<Square>> grid; // Struktura przechowuj�ca kwadraty

    // Petla po kolumnach
    while (x_square <= width - size) {
        std::vector<Square> squares_rows;
        y_square = 0;
        // Petla po wierszach
        while (y_square <= height - size) {
            squares_rows.emplace_back(x_square, y_square, "white", size);
            y_square += size;
        }
        grid.push_back(squares_rows);
        x_square += size;
    }

    return grid;
}

void squares_print(sf::RenderWindow& window, const std::vector<std::vector<Square>>& grid) {
    for (const auto& row : grid) {
        for (const auto& square : row) {
            square.draw(window);
        }
    }
}

/*
 * Je�li chodzi o funkcj� main, by�oby dobrze j� oczy�ci�:
 * Podziel wszystkie funkcje na mniejsze podkomponenty, na przyk�ad:
 * W CLionie masz gotowy modu� do tego. Zaznacz kod, kliknij prawym przyciskiem myszy, wybierz opcj� Refactor, a nast�pnie Extract Method.
 *
 * int main(){
 * auto window = new createWindow(); -> Funkcja inicjujaca okno
 * ...
 * }
 *
 * Class createWindow()
 *
 * public:
 * createWindow(){
 *  displayBasicInfo()
 *  ...
 * }
 * */
int main() {
    //displayBasicInfo()
    sf::RenderWindow visualization_KPN(sf::VideoMode(960, 540), "Kamien Papier Nozyce");
    float quantity=k_quantity(visualization_KPN, k_size);
    std::cout << quantity << std::endl;

    auto squares_network = k_maker(visualization_KPN, k_size); // ilosc kwadratow
    std::cout << "ilosc kwadratow po x: " << squares_network.size() << std::endl;
    std::cout << "ilosc kwadratow po y: " << squares_network[1].size() << std::endl;
    //Zdefiniuj warto�ci 4 i 8 jako sta�e, u�ywaj�c du�ych liter i jednoznacznych nazw, na przyk�ad: VOFFSET, XOFFSET.
    //SetColorForSquare() ???
    for(int i=0; i<squares_network[1].size();i++)
    {
        squares_network[i][i].setColor("blue");
        squares_network[i+4][i].setColor("green");
        squares_network[i+8][i].setColor("red");
    }
    //wynie�� do metody i zamie� 1,0,5 na zmienne jak wy�ej
    //cos()
    squares_network[squares_network.size() - 1][squares_network[1].size() - 1].setColor("blue");
    squares_network[squares_network.size() - 1][0].setColor("red");
    squares_network[0][squares_network[1].size() - 1].setColor("green");
    squares_network[0][squares_network[1].size() - 1].setColor("green");
    squares_network[5][0].setColor("blue");

    //squares_network[0][0].move(50, 50);
    //cos2()
    while (visualization_KPN.isOpen()) {
        sf::Event event;
        while (visualization_KPN.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                visualization_KPN.close();
        }
        //ClearWindow()
        visualization_KPN.clear(sf::Color::Black); // Czyszczenie okna na czarno

        // Rysowanie kwadratow
        //DrawSquare()
        squares_print(visualization_KPN, squares_network);

        visualization_KPN.display();
    }

    return 0;
}
