#include <SFML/Graphics.hpp>
#include <vector>

const size_t SCREEN_WIDTH = 600;
const size_t SCREEN_HEIGHT = 600;

class Point {
    private:
        sf::CircleShape shape;
        sf::Vector2f velocity;
        sf::Vector2f force;
        float mass;
        sf::RenderWindow* window;

        void constrain() {
            sf::Vector2f pos = shape.getPosition();
            float r = shape.getRadius();

            if (pos.x - r < 0) {
                shape.setPosition(sf::Vector2f(r, pos.y));
                velocity = sf::Vector2f(-velocity.x, velocity.y);
            }
            if (pos.x + r > SCREEN_WIDTH) {
                shape.setPosition(sf::Vector2f(SCREEN_WIDTH - r, pos.y));
                velocity = sf::Vector2f(-velocity.x, velocity.y);
            }
            if (pos.y - r < 0) {
                shape.setPosition(sf::Vector2f(pos.x, r));
                velocity = sf::Vector2f(velocity.x, -velocity.y);
            }
            if (pos.y + r > SCREEN_HEIGHT) {
                shape.setPosition(sf::Vector2f(pos.x, SCREEN_HEIGHT - r));
                velocity = sf::Vector2f(velocity.x, -velocity.y);
            }
        }

    public:
        Point(sf::Vector2f pos_in, float radius_in, sf::Vector2f velocity_in, sf::Vector2f force_in, float mass_in, sf::Color color, sf::RenderWindow* window_in) 
            : velocity(velocity_in), force(force_in), mass(mass_in), window(window_in) {
                shape.setPosition(pos_in);
                shape.setRadius(radius_in);
                shape.setFillColor(color);
            }

        void render() {
            window->draw(shape); 
        }

        void update(float delta_time) {
            // using F=ma
            // Semi-implicit Euler Method due to ordering of updates
            sf::Vector2f acceleration = force / mass;
            velocity.x += acceleration.x * delta_time;
            velocity.y += acceleration.y * delta_time;

            sf::Vector2f cp = shape.getPosition();
            shape.setPosition(sf::Vector2f(cp.x + velocity.x * delta_time, cp.y + velocity.y * delta_time));
            constrain();
        }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Verlet");
    sf::Clock clock;
    float delta_time;

    // Points vector
    std::vector<Point> vec;
    vec.push_back(Point(sf::Vector2f(50,50), 10, sf::Vector2f(10,20), sf::Vector2f(50,100), 1, sf::Color::White, &window));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        delta_time = clock.restart().asSeconds();
        for (size_t i = 0; i < vec.size(); ++i) {
            vec[i].render();
            vec[i].update(delta_time);
        }
        window.display();
    }
}


