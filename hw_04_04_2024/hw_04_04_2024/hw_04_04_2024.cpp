#include <iostream>
#include <vector>
using namespace std;

__interface IFlyable {
    virtual void Fly() = 0;
};

__interface ISwimable {
    virtual void Swim() = 0;
};

__interface IJumpable {
    virtual void Jump() = 0;
};

__interface ISpeakable {
    virtual void Speak() = 0;
};

class Parrot : public IFlyable, public ISpeakable {
public:
    virtual void Fly() override {
        cout << "Parrot fly...\n";
    }

    virtual void Speak() override {
        cout << "Kesha's wants to eat...Kesha's wants to eat...Kesha's wants to eat...\n";
    }
};

class Dolphin : public ISwimable {
public:
    virtual void Swim() override {
        cout << "Dolphin swim...\n";
    }
};

class Zebra : public IJumpable {
public:
    virtual void Jump() override {
        cout << "Zebra jump...\n";
    }
};

class Eagle : public IFlyable {
public:
    virtual void Fly() override {
        cout << "Eagle fly...\n";
    }
};

__interface Herbivore {
    virtual void SetLife(bool life) = 0;
    virtual void SetWeight(double weight) = 0;

    virtual bool GetLife() = 0;
    virtual double GetWeight() = 0;

    virtual void EatGrass();
};

class WildeBeest : public Herbivore {
private:
    double weight;
    bool life;
public:
    WildeBeest(double weight, bool life) : weight(weight), life(life) {}

    virtual void SetLife(bool life) override {
        this->life = life;
    }

    virtual void SetWeight(double weight) override {
        this->weight = weight;
    }

    virtual bool GetLife() {
        return life;
    }

    virtual double GetWeight() {
        return weight;
    }

    virtual void EatGrass() override {
        cout << "WildeBeest eat grass...\n";
        weight += 10;
    }
};

__interface Carnivore {
    virtual void SetPower(int power);

    virtual int GetPower() const;

    virtual void Eat(Herbivore* herbivore);
};

class Lion : public Carnivore {
private:
    int power;
public:
    Lion(int power) : power(power) {}

    virtual void SetPower(int power) override {
        this->power = power;
    }

    virtual int GetPower() const override {
        return power;
    }

    virtual void Eat(Herbivore* herbivore) override {
        if (power < herbivore->GetWeight()) {
            cout << "Lion eat Herbivore...\n";
            power -= 10;
        }
        else {
            cout << "Lion eat Herbivore...\n";
            herbivore->SetLife(false);
        }
    }
};

__interface Continent {
    virtual void AddHerbivore(Herbivore* herbivore);
    virtual void AddCarnivore(Carnivore* carnivore);
    virtual void MealsHerbivores();
    virtual void NutritionCarnivores();
};

class Africa : public Continent {
private:
    vector<Herbivore*> herbivores;
    vector<Carnivore*> carnivores;

public:
    virtual void AddHerbivore(Herbivore* herbivore) override {
        herbivores.push_back(herbivore);
    }

    virtual void AddCarnivore(Carnivore* carnivore) override {
        carnivores.push_back(carnivore);
    }

    virtual void MealsHerbivores() override {
        for (auto& herbivore : herbivores) {
            herbivore->EatGrass();
        }
    }

    virtual void NutritionCarnivores() override {
        for (auto& carnivore : carnivores) {
            for (auto& herbivore : herbivores) {
                carnivore->Eat(herbivore);
            }
        }
    }
};

class AnimalWorld {
public:
    virtual void MealsHerbivores(Continent* continent) {
        continent->MealsHerbivores();
    }

    virtual void NutritionCarnivores(Continent* continent) {
        continent->NutritionCarnivores();
    }
};

int main() {
    WildeBeest* h = new WildeBeest(500, true);
    Lion* lion = new Lion(200);

    Africa a;
    a.AddHerbivore(h);
    a.AddCarnivore(lion);

    AnimalWorld world;
    world.MealsHerbivores(&a);
    world.NutritionCarnivores(&a);

    Parrot parrot;
    Dolphin dolphin;
    Zebra zebra;
    Eagle eagle;

    parrot.Fly();
    parrot.Speak();
    dolphin.Swim();
    zebra.Jump();
    eagle.Fly();

    delete h;
    delete lion;
}