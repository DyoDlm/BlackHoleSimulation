#ifndef BLACKHOLE_HPP
#define  BLACKHOLE_HPP

#define ZOOM 10'000'000
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const double G = 6.67430e-11;
const double c = 299792458.0;

struct BlackHole {
    glm::vec2 position;
    double mass;
    double r_s; // rayon de Schwarzschild

    BlackHole(glm::vec2 pos, double m) : position(pos), mass(m) {
        r_s = (2.0 * G * mass) / (c * c) * ZOOM;
    }

    void draw() const {
        // Pour la visibilité, on applique un facteur d'échelle
        const double scale = 1e9;
        float radius = static_cast<float>(r_s * scale);

        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(position.x, position.y); // centre
        int segments = 100;
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * M_PI * i / segments;
            float x = position.x + cos(angle) * radius;
            float y = position.y + sin(angle) * radius;
            glVertex2f(x, y);
        }
        glEnd();
    }
};

struct Ray
{
    double  x;
    double  y;
    glm::vec2 dir;
    std::vector<glm::vec2> path; // historique des positions

    Ray() : x(0), y(0), dir(glm::vec2(0, 0)) {
        path.emplace_back(x, y);
    }

    Ray(glm::vec2 pos, glm::vec2 dir) : x(pos.x), y(pos.y), dir(dir) {
        path.push_back(pos);
    }

    void draw() {
        glColor3f(1, 1, 1);
        glBegin(GL_LINE_STRIP);
        for (const auto& p : path)
            glVertex2f(p.x, p.y);
        glEnd();
    }

    void step() {
        x += dir.x;  // c/c inutile ici, tu peux juste faire +dir.x
        y += dir.y;
        path.emplace_back(x, y); // enregistrer la nouvelle position
    }
};

#endif