#include <random>
#include <list>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Stand
{
public:

    static vector<ConvexShape> _Stands;

    Stand()
    {
        _Stands.resize(8);

        _Stands[0].setPointCount(4);
        _Stands[0].setPoint(0, Vector2f(0.f, 800.f));
        _Stands[0].setPoint(1, Vector2f(300.f, 800.f));
        _Stands[0].setPoint(2, Vector2f(300.f, 900.f));
        _Stands[0].setPoint(3, Vector2f(0.f, 900.f));

        _Stands[1].setPointCount(4);
        _Stands[1].setPoint(0, Vector2f(300.f, 800.f));
        _Stands[1].setPoint(1, Vector2f(550.f, 700.f));
        _Stands[1].setPoint(2, Vector2f(550.f, 900.f));
        _Stands[1].setPoint(3, Vector2f(300.f, 900.f));

        _Stands[2].setPointCount(4);
        _Stands[2].setPoint(0, Vector2f(550.f, 700.f));
        _Stands[2].setPoint(1, Vector2f(650.f, 750.f));
        _Stands[2].setPoint(2, Vector2f(650.f, 900.f));
        _Stands[2].setPoint(3, Vector2f(550.f, 900.f));

        _Stands[3].setPointCount(4);
        _Stands[3].setPoint(0, Vector2f(650.f, 750.f));
        _Stands[3].setPoint(1, Vector2f(800.f, 750.f));
        _Stands[3].setPoint(2, Vector2f(800.f, 900.f));
        _Stands[3].setPoint(3, Vector2f(650.f, 900.f));

        _Stands[4].setPointCount(4);
        _Stands[4].setPoint(0, Vector2f(800.f, 750.f));
        _Stands[4].setPoint(1, Vector2f(950.f, 680.f));
        _Stands[4].setPoint(2, Vector2f(950.f, 900.f));
        _Stands[4].setPoint(3, Vector2f(800.f, 900.f));

        _Stands[5].setPointCount(4);
        _Stands[5].setPoint(0, Vector2f(950.f, 680.f));
        _Stands[5].setPoint(1, Vector2f(1150.f, 680.f));
        _Stands[5].setPoint(2, Vector2f(1150.f, 900.f));
        _Stands[5].setPoint(3, Vector2f(950.f, 900.f));

        _Stands[6].setPointCount(4);
        _Stands[6].setPoint(0, Vector2f(1150.f, 680.f));
        _Stands[6].setPoint(1, Vector2f(1350.f, 800.f));
        _Stands[6].setPoint(2, Vector2f(1350.f, 900.f));
        _Stands[6].setPoint(3, Vector2f(1150.f, 900.f));

        _Stands[7].setPointCount(4);
        _Stands[7].setPoint(0, Vector2f(1350.f, 800.f));
        _Stands[7].setPoint(1, Vector2f(1600.f, 800.f));
        _Stands[7].setPoint(2, Vector2f(1600.f, 900.f));
        _Stands[7].setPoint(3, Vector2f(1350.f, 900.f));

        for (int i = 0; i < _Stands.size(); i++)
            _Stands[i].setFillColor(Color::Cyan);
    }

    void draw(RenderWindow& window)
    {
        for (int i = 0; i < _Stands.size(); i++)
            window.draw(_Stands[i]);
    }

};

class Gun
{
public:

    static float _SaveAngle;

    Gun()
    {
        _StandGun.setSize(Vector2f(72.f, 72.f));
        _StandGun.setPosition(100.f, 800.f - _StandGun.getGlobalBounds().height);
        _StandGun.setFillColor(Color(150, 150, 150));

        _Gun.setSize(Vector2f(16.f, 60.f));
        _GunPosX = 100.f + _StandGun.getGlobalBounds().width / 2.f;
        _GunPosY = 800.f - _StandGun.getGlobalBounds().height / 2.f;
        _Gun.setPosition(_GunPosX, _GunPosY);
        _Gun.setFillColor(Color(170, 170, 255));
        _Gun.setOrigin(_Gun.getSize().x / 2.f, _Gun.getSize().y);

    }
    void  trunkRotation(Vector2f musePos)
    {
        Vector2f dir = musePos - _Gun.getPosition();
        _Angle = atan2(dir.y, dir.x) * 180 / 3.14159265 + 90.f;
        if (_Angle >= 0 && _Angle < 90)
        {
            _Gun.setRotation(_Angle);
            _SaveAngle = _Gun.getRotation();
        }
    }

    void draw(RenderWindow& window)
    {
        window.draw(_StandGun);
        window.draw(_Gun);
    }

protected:
    RectangleShape _StandGun;
    RectangleShape _Gun;
    float _GunPosX;
    float _GunPosY;
    float _Angle;
};

random_device random;
mt19937 generate(random());
class Shapes
{
public:

    bool operator<(const Shapes& other) const
    {
        return getPos().x < other.getPos().x;
    }
    virtual void draw(RenderWindow& window) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual float getHeight() const = 0;
    virtual void setOrigin(float x, float y) = 0;
    virtual void setRotation(float _Angle) = 0;
    virtual Vector2f getCenter() const = 0;
    virtual Vector2f getPos() const = 0;
};

class Ball : public Shapes
{
public:

    Ball()
    {
        _Shape.setRadius(20.f);
        _Shape.setFillColor(Color(255, 225, 255));
    }

    void setPosition(float x, float y)
    {
        _Shape.setPosition(x, y);
    }

    float  getHeight() const
    {
        return _Shape.getGlobalBounds().height;
    }

    void setOrigin(float x, float y)
    {
        _Shape.setOrigin(x, y);
    }

    void setRotation(float _Angle)
    {
        _Shape.setRotation(_Angle);

    }

    Vector2f getCenter() const
    {
        float rotateX = 20 * cos(_Shape.getRotation() * 3.14159 / 180) + 20 * sin(_Shape.getRotation() * 3.14159 / 180);
        float rotateY = 20 * sin(_Shape.getRotation() * 3.14159 / 180) - 20 * cos(_Shape.getRotation() * 3.14159 / 180);
        return _Shape.getPosition() + Vector2f(rotateX, rotateY);
    }

    Vector2f getPos() const
    {
        return  _Shape.getPosition();
    }

    Vector2f getOrigin()
    {

        return _Shape.getOrigin();
    }

    void draw(RenderWindow& window)override
    {
        window.draw(_Shape);
    }

private:
    CircleShape _Shape;
};

class Cube : public Shapes
{
public:

    Cube()
    {
        _Shape.setSize(Vector2f(40.f, 40.f));
        _Shape.setFillColor(Color::Yellow);
    }

    void setPosition(float x, float y)
    {
        _Shape.setPosition(x, y);
    }

    float getHeight() const
    {
        return _Shape.getGlobalBounds().height;
    }

    void setOrigin(float x, float y)
    {
        _Shape.setOrigin(x, y);
    }

    void setRotation(float _Angle)
    {
        _Shape.setRotation(_Angle);
    }

    Vector2f getCenter() const
    {
        float rotateX = 20 * cos(_Shape.getRotation() * 3.14159 / 180) + 20 * sin(_Shape.getRotation() * 3.14159 / 180);
        float rotateY = 20 * sin(_Shape.getRotation() * 3.14159 / 180) - 20 * cos(_Shape.getRotation() * 3.14159 / 180);
        return _Shape.getPosition() + Vector2f(rotateX, rotateY);
    }

    Vector2f getPos() const
    {
        return  _Shape.getPosition();
    }

    Vector2f getOrigin()
    {

        return _Shape.getOrigin();
    }

    void draw(RenderWindow& window)
    {
        window.draw(_Shape);
    }

private:
    RectangleShape _Shape;
};

vector<ConvexShape> Stand::_Stands;
class Objects
{

public:

    int _Choose;
    vector<unique_ptr<Shapes>> _Objects;

    void CreateObjects()
    {
        _Objects.clear();
        for (int i = 0; i < 8; i++)
        {
            _Choose = random() % 2;
            if (_Choose == 0)
            {
                _Objects.push_back(make_unique<Ball>());
            }
            else
            {
                _Objects.push_back(make_unique<Cube>());
            }
        }
    }

    void spawnObjects()
    {
        for (auto& o : _Objects)
        {
            bool cycle = true;
            float newAngle;
            while (cycle)
            {
                _Pos.x = random() % 1250 + 302;
                bool intersec = false;
                for (size_t i = 0; i < Stand::_Stands.size(); i++)
                {
                    float x1 = Stand::_Stands[i].getPoint(0).x;
                    float y1 = Stand::_Stands[i].getPoint(0).y;
                    float x2 = Stand::_Stands[i].getPoint(1).x;
                    float y2 = Stand::_Stands[i].getPoint(1).y;
                    if ((int)_Pos.x > (int)x1 + 5 && _Pos.x < (int)x2 - 45)
                    {
                        if (x2 - x1 != 0)
                        {
                            float y = y1 + ((y2 - y1) / (x2 - x1)) * (_Pos.x - x1);
                            _Pos.y = (int)y;
                            for (auto& other : _Objects)
                            {
                                if (o != other)
                                {
                                    const Vector2f pos1 = _Pos;
                                    const Vector2f pos2 = other->getPos();
                                    if (sqrt((pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y)) < 45.f)
                                    {
                                        intersec = true;
                                        break;
                                    }
                                }
                            }
                            if (!intersec)
                            {
                                cycle = false;
                                float  dx = (int)Stand::_Stands[i].getPoint(1).x - (int)Stand::_Stands[i].getPoint(0).x;
                                float dy = (int)Stand::_Stands[i].getPoint(1).y - (int)Stand::_Stands[i].getPoint(0).y;
                                newAngle = atan2(dy, dx) * 180 / 3.14159;
                                o->setPosition(_Pos.x, _Pos.y);
                                o->setOrigin(0.f, 40.f);
                                o->setRotation(newAngle);
                                break;
                            }
                        }
                    }
                }
            }
        }
        /*for (auto it = objects.begin(); it != objects.end(); ++it)
        {
            bool swapped = false;
            for (auto innerIt = objects.begin(); innerIt != it; ++innerIt)
            {
                if (*innerIt > *it)
                {
                    iter_swap(it, innerIt);
                    swapped = true;
                }
            }
            if (!swapped)
            {
                break;
            }
        }*/
        for (auto it = _Objects.begin(); it != _Objects.end(); ++it)
        {
            for (auto innerIt = next(it); innerIt != _Objects.end(); ++innerIt)
            {
                if (*innerIt < *it)
                {
                    iter_swap(it, innerIt);
                }
            }
        }
    }

    void drawObjects(RenderWindow& window)
    {
        for (auto& o : _Objects)
        {
            o->draw(window);
        }
    }

private:
    Vector2f _Pos;
};

float getLen(Vector2f vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

const Vector2f SquareSize(10.f, 20.f);
class Patron
{
public:
    CircleShape _Shape;
    Vector2f _V;
    RectangleShape _Square;

    Patron()
    {
        _Shape.setRadius(5.f);
        _Shape.setFillColor(Color::Green);

        _Square.setSize(SquareSize);
    }

    Vector2f getCenter() const
    {
        return _Shape.getPosition() + Vector2f(5.f, 5.f);
    }

    void move(int TimeDiff)
    {
        _A = Vector2f(0.f, 0.001f);
        _V.x = _V.x;
        _V.y += _A.y * TimeDiff;
        _Shape.move(_V * (float)TimeDiff);
    }

    void draw(RenderWindow& window)
    {
        window.draw(_Shape);
        window.draw(_Square);
    }

private:
    Vector2f _A;
    float _Gravity;
    bool  _IsAddKspeed = false;
};

float Gun::_SaveAngle;

Font font;
class ListPatrons : public Gun
{
public:
    int _Index = 0;
    int _TempIndex = 0;
    vector<Patron> _Patrons;
    list<Patron> _ShowPatrons;
    Text _CountPatrons;
    int _CountP = 10;
    ListPatrons()
    {
        string FileName = "D:\\изучение c++\\StrikeGame\\x64\\Debug\\font\\ofont.ru_Europe.ttf";
        if (!font.loadFromFile(FileName))
        {
            cout << "error" << endl;
        }
    }

    void createPatrons()
    {
        _Patrons.clear();
        for (int i = 0; i < 10; i++)
        {
            _Patrons.emplace_back();
        }
    }
    void intersectObj(Objects& o)
    {
        vector<Patron>::iterator it;
        for (it = _Patrons.begin(); it < _Patrons.begin() + _Index;)
        {
            bool intersecObj = false;
            bool intersecStand = false;
            bool intersecScreen = false;
            for (auto objIt = o._Objects.begin(); objIt != o._Objects.end(); ++objIt)
            {
                float dx = abs(it->getCenter().x - (*objIt)->getCenter().x);
                float dy = abs(it->getCenter().y - (*objIt)->getCenter().y);
                if (dx <= 40.f / 2 + 5.f && dy <= 40.f / 2 + 5.f)
                {
                    intersecObj = true;
                    objIt = o._Objects.erase(objIt);
                    break;
                }
            }
            for (size_t i = 0; i < Stand::_Stands.size(); i++)
            {
                float dx = Stand::_Stands[i].getPoint(1).x - Stand::_Stands[i].getPoint(0).x;
                float dy = Stand::_Stands[i].getPoint(1).y - Stand::_Stands[i].getPoint(0).y;
                float dist = sqrt(dx * dx + dy * dy);

                float x0 = it->getCenter().x;
                float y0 = it->getCenter().y;

                float t = ((x0 - Stand::_Stands[i].getPoint(0).x) * dx + (y0 - Stand::_Stands[i].getPoint(0).y) * dy) / (dist * dist);
                float projectionX = Stand::_Stands[i].getPoint(0).x + t * dx;
                float projectionY = Stand::_Stands[i].getPoint(0).y + t * dy;
                if (t >= 0 && t <= 1 && sqrt((projectionX - x0) * (projectionX - x0) + (projectionY - y0) * (projectionY - y0)) <= 5.f)
                {
                    intersecStand = true;
                    break;
                }
            }
            if (it->_Shape.getPosition().x >= 1590.f || it->_Shape.getPosition().y <= 0.f)
            {
                intersecScreen = true;
            }
            if (intersecObj || intersecStand || intersecScreen)
            {
                it = _Patrons.erase(it);
                _Index--;
                _TempIndex--;
            }
            else
            {
                ++it;
            }
        }
    }

    void countPatrons()
    {
        Vector2f pos;
        float centerStandGunX = _StandGun.getPosition().x + (_StandGun.getSize().x - SquareSize.x) / 2;
        pos.x = centerStandGunX - 77;
        pos.y = 840.f;
        _ShowPatrons.clear();
        for (int i = 0; i < 10; i++)
        {
            _ShowPatrons.emplace_back();
            _ShowPatrons.back()._Square.setPosition(pos.x, pos.y);
            pos.x += SquareSize.x + 6.f;
        }
    }

    void outText()
    {
        Vector2f pos;
        float centerStandGunX = _StandGun.getPosition().x + (_StandGun.getSize().x - SquareSize.x) / 2;
        pos.x = centerStandGunX - _CountPatrons.getGlobalBounds().width / 2;
        pos.y = 810;
        _CountPatrons.setFont(font);
        _CountPatrons.setCharacterSize(20);
        _CountPatrons.setFillColor(Color::Black);
        _CountPatrons.setString(L"Number of patrons: " + to_string(_CountP));
        _CountPatrons.setPosition(pos.x, pos.y);
    }

    void spawn(float _Angle)
    {
        if (_Index >= _Patrons.size())
        {
            return;
        }
        float angleRad = _Angle * (3.14159 / 180);
        float GunX = _Gun.getPosition().x + _Gun.getSize().y * sin(angleRad);
        float GunY = _Gun.getPosition().y - _Gun.getSize().y * cos(angleRad);
        _Patrons[_Index]._Shape.setPosition(GunX - 5, GunY - 5);
    }
    void move(int TimeDiff)
    {
        int max = _TempIndex;
        if (max >= _Patrons.size())
        {
            max--;
        }
        for (int i = 0; i <= max; i++)
        {
            _Patrons[i].move(TimeDiff);
        }
    }

    void draw(RenderWindow& window)
    {
        int max = _Index;
        if (max >= _Patrons.size())
        {
            max--;
        }
        for (int i = 0; i <= max; i++)
        {
            window.draw(_Patrons[i]._Shape);
        }
        for (auto& showPat : _ShowPatrons)
        {
            window.draw(showPat._Square);
        }
        window.draw(_CountPatrons);
    }
private:

};
int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(1600, 900), "AngryGame", Style::Default, settings);

    Stand _stand;
    Gun _gun;
    Objects _objects;
    ListPatrons _patrons;

    Clock clock;
    Time time = clock.getElapsedTime();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::MouseMoved)
            {
                _gun.trunkRotation(Vector2f(event.mouseMove.x, event.mouseMove.y));
            }
            /*if (Mouse::isButtonPressed(Mouse::Left))
            {
               //Patrons::Kspeed += 0.1f;

            }*/
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
            {
                if (_patrons._Index < _patrons._Patrons.size())
                {
                    _patrons._Patrons[_patrons._Index]._V.x = 1.24f * cos((Gun::_SaveAngle - 90) * (3.14159 / 180));
                    _patrons._Patrons[_patrons._Index]._V.y = 1.24f * sin((Gun::_SaveAngle - 90) * (3.14159 / 180));

                    _patrons._TempIndex = _patrons._Index;
                    _patrons._Index++;
                    _patrons._ShowPatrons.pop_back();
                    if (_patrons._CountP != 0)
                        _patrons._CountP--;
                }
            }
            if (event.type == Event::Closed)
                window.close();
        }
        Time time2 = clock.getElapsedTime();
        int diff = time2.asMilliseconds() - time.asMilliseconds();
        time = time2;
        if (_patrons._Patrons.empty() || _objects._Objects.empty())
        {
            _patrons.createPatrons();
            _patrons.countPatrons();
            _patrons._CountP = 10;
            _objects._Objects.clear();
            _objects.CreateObjects();
            _objects.spawnObjects();
        }
        _patrons.outText();
        _patrons.spawn(Gun::_SaveAngle);
        _patrons.intersectObj(_objects);
        if (_patrons._Index > _patrons._TempIndex)
            _patrons.move(diff);

        window.clear();
        _stand.draw(window);
        _objects.drawObjects(window);
        _patrons.draw(window);
        _gun.draw(window);
        window.display();
    }
    return 0;
}