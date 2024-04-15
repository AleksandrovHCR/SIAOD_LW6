#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
int* Fill(int* Grav, int Size) {
	int input;
	Grav = (int*)malloc(Size * sizeof(int));
	printf("Enter the values:");
	for (int i = 0; i < Size; i++) {
		scanf("%d", &input);
		*(Grav + i) = input;
	}
	return Grav;
}
void Reveal(int* Grav, int Size) {
	int i = 0;
	printf(" |");
	while (i < Size) {
		printf(" \x1B[36m%d\033[0m ", *(Grav + i));
		i++;
	}
	printf(" |\n");
}



//В файл
void TF_rec(int* Grav, int Size) {
	FILE* F = fopen("TMP.txt", "w");
	int count = 0;
	while (count < Size) {
		fprintf(F, "%d", *(Grav + count));
		if (count != Size - 1)
			fprintf(F, " ");
		count++;
	}
	//fprintf(F, "%d", EOF);
	fclose(F);
}
//Из файла
int* decode(int* Grav, int* S, char* name) {
	FILE* F = fopen(name, "r");
	int Size = 0, x;
	if ((F = fopen(name, "r")) == NULL) {
		printf("\nFile is not exist...");
		return 0;
	}
	else {
		while (!feof(F)) {
			fscanf(F, "%d", &x);
			Size++;
		}
		*S = Size;
		Grav = (int*)malloc(Size * sizeof(int));
		fclose(F);
		FILE* F = fopen(name, "r");
		int i = 0;
		while (!feof(F)) {
			fscanf(F, "%d ", &x);
			*(Grav + i) = x;
			i++;
		}
		return Grav;
	}
}


//Естественное слияние
void est_sort(int* Grav, int Size) {
	while (true) {
		FILE* F1 = fopen("S1.txt", "w"), * F2 = fopen("S2.txt", "w");
		int tf1 = 0, tf2 = 0, temp, count = 0;
		bool p1_l_p2 = true;
		printf("Fission:\n");
		while (count < Size) {
			int t1 = *(Grav + count), t2 = *(Grav + count + 1);
			if (p1_l_p2) {
				fprintf(F1, "%d", t1);
				fprintf(F1, " ");
				printf("\n%d => F1\n", t1);
				tf1++;
				if (t1 > t2)
					p1_l_p2 = false;
			}
			else {
				fprintf(F2, "%d", t1);
				fprintf(F2, " ");
				printf("\n%d => F2\n", t1);
				tf2++;
				if (t1 <= t2)
					p1_l_p2 = true;
			}
			count++;
		}
		fclose(F1);
		fclose(F2);
		//reveal
		printf("\n\x1B[96mArray is divided on files:\033[0m\n");
		printf("F1: ");
		F1 = fopen("S1.txt", "r");
		F2 = fopen("S2.txt", "r");
		for (int y = 0; y < tf1; y++) {
			fscanf(F1, "%d ", &temp);
			printf("%d ", temp);
		}
		printf("\nF2: ");
		for (int y = 0; y < tf2; y++) {
			fscanf(F2, "%d ", &temp);
			printf("%d ", temp);
		}
		fclose(F1);
		fclose(F2);
		if (tf1 == 0 || tf2 == 0) {
			printf("\n");
			remove("S1.txt");
			remove("S2.txt");
			break;
		}
		printf("\n\x1B[31mFusion:\033[0m\n");
		//to array

		F1 = fopen("S1.txt", "r");
		F2 = fopen("S2.txt", "r");
		count = 0;
		int t1, t2;
		fscanf(F1, "%d ", &t1);
		fscanf(F2, "%d ", &t2);

		while (count < Size) {
			printf("\n\x1B[91mComparison: %d <-> %d\033[0m", t1, t2);
			if ((t1 <= t2 && tf1 > 0) || tf2 == 0) {
				*(Grav + count) = t1;
				fscanf(F1, "%d ", &t1);
				tf1--;
			}
			else {
				if ((t2 <= t1 && tf2 > 0) || tf1 == 0) {
					*(Grav + count) = t2;
					fscanf(F2, "%d ", &t2);
					tf2--;
				}
			}
			count++;
			printf("\n");
			for (int u = 0; u < Size; u++) {
				if (u != count - 1)
					printf("%d ", *(Grav + u));
				else
					printf("\x1B[31m%d \033[0m", *(Grav + u));
			}
		}
		fclose(F1);
		fclose(F2);
		printf("\n");
		system("pause");

	}
}
//Двухфазная сортировка простым слиянием
void TFSORT(int* Grav, int Size) {
	int a1, a2, i, j, tmp;
	FILE* F1, * F2;
	int Series = 1;
	while (Series < Size) {

		tmp = 0;
		printf("Series: %d\n", Series);
		F1 = fopen("T_Sort1.txt", "w");
		F2 = fopen("T_Sort2.txt", "w");
		printf("\x1B[32mFission:\033[0m\n");
		//fission
		while (tmp < Size) {
			for (int i = 0; i < Series && tmp < Size; i++) {
				fprintf(F1, "%d ", *(Grav + tmp));
				printf("%d -> F1\n", *(Grav + tmp));

				tmp++;
			}
			for (int j = 0; j < Series && tmp < Size; j++) {
				fprintf(F2, "%d ", *(Grav + tmp));
				printf("%d -> F2\n", *(Grav + tmp));

				tmp++;
			}
		}
		fclose(F1);
		fclose(F2);
		F1 = fopen("T_Sort1.txt", "r");
		F2 = fopen("T_Sort2.txt", "r");
		//reveal
		printf("\n\x1B[93mArray is divided on files:\033[0m");
		printf("\nF1:");
		while (!feof(F1)) {
			fscanf(F1, "%d ", &a1);
			printf("%d ", a1);
		}
		printf("\nF2:");
		while (!feof(F2)) {
			fscanf(F2, "%d ", &a1);
			printf("%d ", a1);
		}
		fclose(F1);
		fclose(F2);
		//merge
		printf("\n\x1B[33mFusion:\033[0m\n");
		F1 = fopen("T_Sort1.txt", "r");
		F2 = fopen("T_Sort2.txt", "r");
		tmp = 0;
		if (!feof(F1)) fscanf(F1, "%d", &a1);
		if (!feof(F2)) fscanf(F2, "%d", &a2);
		while (!feof(F1) && !feof(F2)) {
			i = 0;
			j = 0;
			while (i < Series && j < Series && !feof(F1) && !feof(F2)) {
				printf("\n\x1B[92mComparison: %d <-> %d\033[0m", a1, a2);
				if (a1 < a2) {
					*(Grav + tmp) = a1;
					fscanf(F1, "%d", &a1);
					i++;
					printf("\n");
					for (int p = 0; p < Size; p++) {
						if (p == tmp)
							printf(" \x1B[33m%d\033[0m ", *(Grav + p));
						else
							printf("%d ", *(Grav + p));
					}
					tmp++;
				}
				else {
					*(Grav + tmp) = a2;
					fscanf(F2, "%d", &a2);
					j++;
					printf("\n");
					for (int p = 0; p < Size; p++) {
						if (p == tmp)
							printf(" \x1B[33m%d\033[0m ", *(Grav + p));
						else
							printf("%d ", *(Grav + p));
					}
					tmp++;
				}
			}
			while (i < Series && !feof(F1) && tmp < Size) {
				*(Grav + tmp) = a1;
				fscanf(F1, "%d", &a1);

				printf("\n");
				for (int p = 0; p < Size; p++) {
					if (p == tmp)
						printf(" \x1B[33m%d\033[0m ", *(Grav + p));
					else
						printf("%d ", *(Grav + p));
				}

				tmp++;

				i++;
			}
			while (j < Series && !feof(F2) && tmp < Size) {
				*(Grav + tmp) = a2;
				fscanf(F2, "%d", &a2);

				printf("\n");
				for (int p = 0; p < Size; p++) {
					if (p == tmp)
						printf(" \x1B[33m%d\033[0m ", *(Grav + p));
					else
						printf("%d ", *(Grav + p));
				}

				tmp++;
				j++;
			}
		}
		////////////
		while (!feof(F1) && tmp < Size) {
			*(Grav + tmp) = a1;
			fscanf(F1, "%d", &a1);

			printf("\n");
			for (int p = 0; p < Size; p++) {
				if (p == tmp)
					printf(" \x1B[33m%d\033[0m ", *(Grav + p));
				else
					printf("%d ", *(Grav + p));
			}


			tmp++;
		}
		while (!feof(F2) && tmp < Size) {
			*(Grav + tmp) = a2;
			fscanf(F2, "%d", &a2);

			printf("\n");
			for (int p = 0; p < Size; p++) {
				if (p == tmp)
					printf(" \x1B[33m%d\033[0m ", *(Grav + p));
				else
					printf("%d ", *(Grav + p));
			}


			tmp++;
		}
		fclose(F2);
		fclose(F1);
		printf("\n");
		system("pause");
		Series *= 2;

	}
	remove("T_Sort1.txt");
	remove("T_Sort2.txt");
}
//Однофазная сортировка простым слиянием (Адъ)
void OFSORT(int* Grav, int Size) {

}




void main() {
	int* Array = NULL, size;
	char select;
	while (1) {
		if (Array)
			Reveal(Array, size);
		printf(" +-------------\x1B[96mMENU\033[0m------------------+\n");
		printf("+|         \x1B[96m1.New array\033[0m               |+\n");
		printf("+|         \x1B[96m2.Sort(Natural fusion)\033[0m    |+\n");
		printf("+|         \x1B[96m3.Sort(Two phases)\033[0m        |+\n");
		printf("+|         \x1B[96m4.Sort(One phase)\033[0m         |+\n");
		printf("+|         \x1B[96m5.Read from file \033[0m         |+\n");
		printf(" +-----------------------------------+\n");
		printf("Select the item:");
		scanf("%s", &select);
		switch (select) {
		case '1':
			printf("Enter the size of array:");
			scanf("%d", &size);
			Array = Fill(Array, size);
			break;
		case '2':
			est_sort(Array, size);
			printf("\n+----------Message----------+");
			printf("\n| Array sorted and recorded |");
			printf("\n+---------------------------+\n");
			TF_rec(Array, size);
			break;
		case '3':
			TFSORT(Array, size);
			printf("\n+----------Message----------+");
			printf("\n| Array sorted and recorded |");
			printf("\n+---------------------------+\n");
			TF_rec(Array, size);
			break;
		case '5':
			char name[20];
			printf("Enter the name:");
			scanf("%s", &name, 20);
			Array = decode(Array, &size, name);
			break;
		default:
			printf("\n+----ERROR-----+");
			printf("\n| Invalid item |");
			printf("\n+--------------+\n");
			break;
		}
		system("pause");
		system("cls");
	}
}