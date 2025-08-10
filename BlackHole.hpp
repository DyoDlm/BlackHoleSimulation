#ifndef BLACKHOLE_HPP
#define  BLACKHOLE_HPP

#define ZOOM 10'000'000
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WI 800
#define HI 600

const double G = 6.67430e-11;
const double c = 299792458.0;
const double scale = 1e9;

struct BlackHole {
    glm::vec2 position;
    double mass;
    double r_s; // rayon de Schwarzschild

    BlackHole(glm::vec2 pos, double m) : position(pos), mass(m) {
        r_s = (2.0 * G * mass) / (c * c) * ZOOM;
    }

    void draw() const {
        // Pour la visibilité, on applique un facteur d'échelle
        float radius = static_cast<float>(r_s * scale);

        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(position.x, position.y); // centre
        int segments = 100;
        for (int i = 0; i <= segments; ++i)
        {
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
    bool absorbed = false;

    //  cartesian
    double  x;
    double  y;

    //  polar coor
    double  r;
    double  phi;
    double  dr;
    double  dphi;
    double  d2r;
    double  d2phi;
    glm::vec2 dir;
    std::vector<glm::vec2> path; // historique des positions

    Ray() : x(0), y(0), dir(glm::vec2(0, 0)) {
        path.emplace_back(x, y);
    }

    Ray(glm::vec2 pos, glm::vec2 dir) : x(pos.x), y(pos.y), dir(dir) {
        //path.push_back(pos);
        r = hypot(x, y);
        phi = atan2(y, x);
        dr = c * cos(phi) + dir.y * sin(phi); // m/s
        dphi = (-c * sin(phi) + dir.y * cos(phi)) / r;
        d2r = 0.0;
        d2phi = 0.0;
    }

    double  getDistance(double x, double y, glm::vec2 c)
    {
        return (sqrt((x - c.x)*(x - c.x) + (y - c.y)*(y - c.y)) / scale);
    }

    void step(const glm::vec2& center, double r_s, float delta = 0.1)
    {
        if (absorbed)
            return ;
    //    double  distance = getDistance(x, y, center);

        dr += d2r * delta;
        dphi += d2phi * delta;
        r += dr * delta;
        phi += dphi * delta;

    //    if (distance <= r_s) {
    //        absorbed = true;
    //        return;
    //    }
//
     //   x += dir.x;
     //   y += dir.y;
        x = cos(phi) + r;
        y = sin(phi) + r;
        path.emplace_back(x, y);
    }

    void zdraw() const
    {
        if (path.empty())
            return;
        glColor3f(1, 1, 1);
        glBegin(GL_LINE_STRIP);
        for (const auto& p : path)
            glVertex2f(p.x, p.y);
        glEnd();
    }
};

void    geodesic(Ray ray, double r_s)
{
    double r = ray.r;
    double phi = ray.phi;
    double dr = ray.dr;
    double dphi = ray.dphi;

    dr += r * dphi * dphi - (c*c*r_s) / (2.0 * r*r);
    dphi = -2.0 * dr * dphi / r;
}

#endif