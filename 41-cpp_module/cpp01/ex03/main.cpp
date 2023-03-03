//
// Created by Junhyuk Ji on 3/3/23.
//

int main(void) {
        Weapon club = Weapon("crude spiked club");
        HumanA bob("Bob", club);
        bob.attack();
        club.setType("some other type of club"); bob.attack();
        return 0; }
}
