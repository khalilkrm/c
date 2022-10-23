struct un_article {
        char description[50];
        float prix;
};

struct stock {
	int nombre_article;
	struct un_article articles[50];
};

