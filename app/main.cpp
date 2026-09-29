#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <sys/types.h>

void welcome();

void help();

void farewell();

enum class Option { Attack, Show, Help, Quit, Pass, Invalid = -1 };

Option option(std::string text_option);

class Entity {
protected:
  std::string name{};
  uint health{};
  uint armor{};
  uint damage{};

public:
  Entity(std::string name, uint health, uint armor, uint damage)
      : name(name), health(health), armor(armor), damage(damage) {};
  virtual void show();
  virtual uint getDamage();
  virtual std::string getName() { return name; }
  virtual uint takeDamage(uint damage);
  bool isAlive() { return health > 0 ? true : false; }
};

class Warrior : public Entity {
public:
  Warrior(std::string name) : Entity(name, 100, 50, 30) {};
};

class Skeleton : public Entity {
public:
  Skeleton() : Entity("Skeleton", 70, 20, 40) {};
};

int main() {
  Entity hero = Warrior{"Alex"};
  Entity enemy = Skeleton{};
  welcome();
  std::string command{};
  while (true) {
    std::cout << "> ";
    getline(std::cin, command);
    switch (option(command)) {
    case Option::Attack: {
      std::cout << hero.getName() << " damage "
                << enemy.takeDamage(hero.getDamage()) << " hp\n";
      if (!enemy.isAlive()) {
        hero.show();
        enemy.show();
        std::cout << "You win\n";
        return 0;
      }
      std::cout << "Enemy damage " << hero.takeDamage(enemy.getDamage())
                << " hp\n";

      if (!hero.isAlive()) {
        std::cout << "You lose\n";
        return 0;
      }
      break;
    }
    case Option::Show: {
      std::string argument{command.substr(5, command.npos)};
      if (argument == "hero") {
        hero.show();
      } else if (argument == "enemy") {
        enemy.show();
      } else {
        std::cout << "invalid argument\ntry \"show <hero/enemy>\"\n";
      }
      break;
    }
    case Option::Help: {
      help();
      break;
    }

    case Option::Quit: {
      farewell();
      return 0;
    }
    case Option::Invalid: {
      std::cout << "try another command, or print \"help\" for information\n";
      break;
    }
    case Option::Pass:
      break;
    }
    std::cout << '\n';
  }
  farewell();
}

Option option(std::string text_option) {
  if (text_option == "attack") {
    return Option::Attack;
  }
  if (text_option == "help") {
    return Option::Help;
  }
  if (text_option.substr(0, 4) == "show") {
    if (text_option.size() < 6) {
      std::cout << "show have too few arguments\ntry \"show <hero/enemy>\"\n";
      return Option::Pass;
    }
    return Option::Show;
  }
  if (text_option == "quit" || text_option == "q") {
    return Option::Quit;
  } else {
    return Option::Invalid;
  }
}

void Entity::show() {
  std::cout << name << ":\n"
            << "hp: " << health << "\nArmor: " << armor
            << "\nDamage: " << damage << "\n";
}

uint Entity::getDamage() { return damage; }

uint Entity::takeDamage(uint damage) {
  uint clear_damage = damage * (1.0 - static_cast<double>(armor) / 100);
  if (clear_damage >= health) {
    clear_damage = health;
    health = 0;
  } else {
    health -= clear_damage;
  }
  return clear_damage;
}

void welcome() {
  std::cout << "Welcome in my mini console rpg game!\nfor more "
               "information print \"help\"\nGood luck!!!\n\n";
}

void help() {
  std::cout << std::left << std::setw(20) << "help" << std::setw(50)
            << "Print for more information" << "\n\n";
  std::cout << std::left << std::setw(20) << "attack" << std::setw(50)
            << "Print to attack enemy" << "\n\n";
  std::cout << std::left << std::setw(20) << "show <hero/enemy>"
            << std::setw(50) << "Print for show detail about hero/enemy"
            << "\n";
}

void farewell() { std::cout << "Thanks for playing!!\n"; }
