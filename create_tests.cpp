#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

std::string randintStr(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(min, max);
  std::ostringstream oss;
  oss << distrib(gen);
  return oss.str();
}

int randint(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(min, max);
  return distrib(gen);
}

std::string randEnseignant(const std::vector<std::string> &noms,
                           const std::vector<std::string> &prenoms) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribNom(0, noms.size() - 1);
  std::uniform_int_distribution<int> distribPrenom(0, prenoms.size() - 1);
  return noms[distribNom(gen)] + " " + prenoms[distribPrenom(gen)];
}

std::string randEmail(const std::string &prenom, const std::string &nom) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(1, 100);
  std::ostringstream oss;
  oss << prenom << "." << nom << distrib(gen) << "@example.com";
  return oss.str();
}

int main() {
  std::ofstream file("tests.sql");

  std::vector<std::string> firstnames = {
      "Jean",      "Marie",   "Claire", "Pierre",    "Sophie",   "Nicolas",
      "Emma",      "Thomas",  "Julie",  "Antoine",   "Camille",  "Lucas",
      "Pauline",   "Louis",   "Laura",  "Alexandre", "Marine",   "Martin",
      "Manon",     "Gabriel", "Alice",  "Romain",    "Caroline", "Mathieu",
      "Charlotte", "Vincent", "Chloé",  "Maxime",    "Elodie",   "Adrien"};

  std::vector<std::string> lastnames = {
      "Dubois",   "Martin",   "Bernard", "Thomas", "Petit",    "Robert",
      "Richard",  "Durand",   "Leroy",   "Moreau", "Simon",    "Laurent",
      "Lefebvre", "Michel",   "Garcia",  "David",  "Bertrand", "Roux",
      "Vincent",  "Fournier", "Morel",   "Girard", "Andre",    "Lefevre",
      "Mercier",  "Dupont",   "Lambert", "Bonnet", "Francois", "Martinez"};

  std::vector<std::string> cours = {"Introduction à l algorithmique",
                                    "Programmation en C++",
                                    "Analyse mathématique",
                                    "Bases de données",
                                    "Structures de données",
                                    "Théorie des graphes",
                                    "Architecture des ordinateurs",
                                    "Cryptographie",
                                    "Systèmes d exploitation",
                                    "Réseaux informatiques",
                                    "Intelligence artificielle",
                                    "Nouvelles technologies",
                                    "Logique mathématique",
                                    "Programmation parallèle",
                                    "Piscine"};

  std::vector<std::string> namesEnseignants = {
      "Lefebvre", "Dubois", "Martin",  "Bernard", "Thomas",
      "Petit",    "Robert", "Richard", "Durand",  "Leroy"};

  std::vector<std::string> firstnamesEnseignants = {
      "Jean",    "Marie", "Claire", "Pierre", "Sophie",
      "Nicolas", "Emma",  "Thomas", "Julie",  "Antoine"};

  std::vector<std::string> cities = {"Montreal", "Quebec", "Trois-Rivieres",
                                     "Chicoutimi", "Rimouski"};

  if (!file.is_open()) {
    std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
    return 1;
  }

  file << "INSERT INTO etudiant (id_etudiant, prenom_etudiant, "
          "nom_etudiant, programme, telephone, email) VALUES"
       << std::endl;
  for (int i = 0; i < 30; ++i) {
    std::string phone = randintStr(100000000, 999999999);
    std::string email = randEmail(firstnames[i], lastnames[i]);
    file << "(" << i + 1 << ", '" << firstnames[i] << "', '" << lastnames[i]
         << "', 'Programme " << (i + 1) << "', '" << phone << "', '" << email
         << "')";
    if (i < 29) {
      file << ",";
      file << std::endl;
    }
  }
  file << ";\n" << std::endl;

  file << "INSERT INTO cours (id_cours, nom_du_cours, nombre_heures, "
          "enseignant) VALUES"
       << std::endl;
  for (int i = 0; i < 15; ++i) {
    std::string name = randEnseignant(namesEnseignants, firstnamesEnseignants);

    file << "(" << i + 1 << ", '" << cours[i] << "', " << randint(10, 25)
         << ", '" << name << "')";
    if (i < 14) {
      file << ",";
      file << std::endl;
    }
  }
  file << ";\n" << std::endl;

  file << "INSERT INTO cours_suivi (id_cours, id_etudiant, session, local) "
          "VALUES"
       << std::endl;
  for (int i = 0; i < 30; ++i) {
    int idCours = randint(1, 15);
    int idEtudiant = i + 1;
    std::string session = "Session Hiver";
    std::string local = "Local " + randintStr(1, 100);
    file << "(" << idCours << ", " << idEtudiant << ", '" << session << "', '"
         << local << "')";
    if (i < 29) {
      file << ",";
      file << std::endl;
    }
  }
  file << ";\n" << std::endl;

  file << "INSERT INTO universite (id_universite, nom_universite, "
          "sigle_université, adresse_universite, telephone, email, website) "
          "VALUES"
       << std::endl;
  for (int i = 0; i < 5; ++i) {
    std::string phone = randintStr(100000000, 999999999);
    std::string sigle = "UQA";
    std::string city = cities[i];
    sigle.push_back(city[0]);
    file << "(" << i + 1 << ", "
         << "'Universite du Quebec a " << city << "', "
         << "'" << sigle << "', "
         << "'xyz adresse', '" << phone << "', "
         << "'universite." << sigle << "@mail.ca', "
         << "'universite." << sigle << ".ca')";
    if (i < 4) {
      file << ",";
      file << std::endl;
    }
  }
  file << ";\n" << std::endl;

  file << "INSERT INTO agent (id_agent, nom_agent, prenom_agent, telephone, "
          "email) VALUES";
  for (int i = 0; i < 15; ++i) {
    std::string firstname = firstnamesEnseignants[(i + 1) % 10];
    std::string lastname = lastnames[(i + 2) % 10];
    std::string phone = randintStr(100000000, 999999999);
    std::string email = randEmail(firstname, lastname);
    file << "(" << i + 1 << ", '" << lastname << "', '" << firstname << "', '"
         << phone << "', '" << email << "')";
    if (i < 14) {
      file << ",";
      file << std::endl;
    }
  }
  file << ";\n" << std::endl;

  file << "INSERT INTO espace_stationnement(id_espace_stationnement, "
          "designation_espace_stationnement, id_universite) VALUES";
  for (int i = 0; i < 10; ++i) {
    std::string designation = "Espace " + std::to_string((i / 5) + 1);
    ;
    file << "(" << i + 1 << ", '" << designation << "', " << (i % 5) + 1 << ")";
    if (i < 9) {
      file << ",";
      file << std::endl;
    }
  }
  file << ";\n" << std::endl;

  file << "INSERT INTO espace_surveille(id_agent, id_espace_stationnement, "
          "date_surveillance, heure_debut_surveillance, "
          "heure_fin_surveillance) VALUES"
       << std::endl;
  for (int i = 0; i < 10; ++i) {
    int year = 2024; // Année actuelle
    int month = randint(1, 12);
    int day = randint(1, 28); // Suppose que février a 28 jours
    std::string date = std::to_string(year) + "-" + (month < 10 ? "0" : "") +
                       std::to_string(month) + "-" + (day < 10 ? "0" : "") +
                       std::to_string(day);

    int hour_start = randint(0, 23);
    int min_start = randint(0, 59);
    int sec_start = randint(0, 59);
    std::string heure_debut =
        (hour_start < 10 ? "0" : "") + std::to_string(hour_start) + ":" +
        (min_start < 10 ? "0" : "") + std::to_string(min_start) + ":" +
        (sec_start < 10 ? "0" : "") + std::to_string(sec_start);

    int hour_end = hour_start + randint(1, 4);
    if (hour_end > 23) {
      hour_end -= 24;
    };
    int min_end = randint(0, 59);
    int sec_end = randint(0, 59);
    std::string heure_fin =
        (hour_end < 10 ? "0" : "") + std::to_string(hour_end) + ":" +
        (min_end < 10 ? "0" : "") + std::to_string(min_end) + ":" +
        (sec_end < 10 ? "0" : "") + std::to_string(sec_end);

    file << "(" << i + 1 << ", " << i + 1 << ", '" << date << "', '"
         << heure_debut << "', '" << heure_fin << "')";
    if (i < 9) {
      file << ",";
      file << std::endl;
    }
  }
  file << ";\n" << std::endl;

  file << "INSERT INTO allee(id_allee, id_espace_stationnement, "
          "designation_alle, sens_de_circulation) VALUES"
       << std::endl;
  for (int i = 0; i < 10; ++i) {
    int id_allee = i + 1;
    int id_espace_stationnement = randint(1, 10);
    std::string designation_allee = "Allee " + std::to_string(i + 1);
    std::string sens_de_circulation;
    if (randint(0, 1) == 0) {
      sens_de_circulation = "Entrée";
    } else {
      sens_de_circulation = "Sortie";
    }

    file << "(" << id_allee << ", " << id_espace_stationnement << ", '"
         << designation_allee << "', '" << sens_de_circulation << "')";
    if (i < 9) {
      file << ",";
      file << std::endl;
    }
  }
  file << ";\n" << std::endl;

  file << "INSERT INTO place(id_place, type_de_place, id_allee) VALUES"
       << std::endl;
  for (int i = 0; i < 20; ++i) {
    int id_place = i + 1;
    std::string type_de_place;
    int random_type = randint(0, 2);
    switch (random_type) {
    case 0:
      type_de_place = "'standard'";
      break;
    case 1:
      type_de_place = "'personnes à mobilité réduite'";
      break;
    case 2:
      type_de_place = "'véhicules électriques'";
      break;
    }
    int id_allee = randint(1, 10); // Supposons qu'il y a 10 allées

    // Écriture de la ligne d'insertion dans le fichier
    file << "(" << id_place << ", " << type_de_place << ", " << id_allee << ")";
    if (i < 19) {
      file << ",";
      file << std::endl;
    }
  }
  file << ";\n" << std::endl;

  file << "INSERT INTO place_reservee(id_place, id_etudiant, date_reservation, "
          "heure_debut_reservation, heure_fin_reservation) VALUES"
       << std::endl;
  for (int i = 0; i < 20; ++i) {
    int id_place = randint(1, 20);    // Supposons qu'il y a 20 places
    int id_etudiant = randint(1, 30); // Supposons qu'il y a 30 étudiants
    // Génération de la date de réservation aléatoire
    int year = 2024; // Année actuelle
    int month = randint(1, 12);
    int day = randint(1, 28); // Suppose que février a 28 jours
    std::string date_reservation = std::to_string(year) + "-" +
                                   (month < 10 ? "0" : "") +
                                   std::to_string(month) + "-" +
                                   (day < 10 ? "0" : "") + std::to_string(day);

    // Génération de l'heure de début et de fin de la réservation aléatoire
    int hour_start = randint(8, 17); // Réservation possible de 8h à 17h
    int min_start = randint(0, 59);
    int sec_start = randint(0, 59);
    std::string heure_debut_reservation =
        (hour_start < 10 ? "0" : "") + std::to_string(hour_start) + ":" +
        (min_start < 10 ? "0" : "") + std::to_string(min_start) + ":" +
        (sec_start < 10 ? "0" : "") + std::to_string(sec_start);

    int hour_end =
        hour_start + randint(1, 4); // Supposons une réservation de 1 à 4 heures
    if (hour_end > 17)
      hour_end = 17; // Limiter l'heure de fin à 17h
    int min_end = randint(0, 59);
    int sec_end = randint(0, 59);
    std::string heure_fin_reservation =
        (hour_end < 10 ? "0" : "") + std::to_string(hour_end) + ":" +
        (min_end < 10 ? "0" : "") + std::to_string(min_end) + ":" +
        (sec_end < 10 ? "0" : "") + std::to_string(sec_end);

    // Écriture de la ligne d'insertion dans le fichier
    file << "(" << id_place << ", " << id_etudiant << ", '" << date_reservation
         << "', '" << heure_debut_reservation << "', '" << heure_fin_reservation
         << "')";
    if (i < 19) {
      file << ",";
      file << std::endl;
    }
  }
  file << ";\n" << std::endl;

  file.close();

  std::cout << "'tests.sql' created." << std::endl;

  return 0;
}
