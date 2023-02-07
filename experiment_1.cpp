#include <math.h>
#include <iostream>

using namespace std;

typedef struct PolyNode {
    double coef;
    int exp;
    struct PolyNode* next;
}* Polynomial;

Polynomial InitPolynomial();
void DestroyPolynomial(Polynomial& Poly);
void PrintPolynomial(Polynomial Poly);
void PrintTerm(Polynomial term, bool isFirst);
Polynomial CopyPolynomial(Polynomial& Poly);
Polynomial InsertPolyNode(Polynomial& Poly, Polynomial& node);
Polynomial PolynomialAddition(Polynomial Poly1, Polynomial Poly2);
Polynomial PolynomialSubtraction(Polynomial Poly1, Polynomial Poly2);
Polynomial PolynomialMultiplication(Polynomial Poly1, Polynomial Poly2);
Polynomial PolynomialDivision(Polynomial Poly1, Polynomial Poly2);
Polynomial QuotientOrRemainder(Polynomial Poly, bool isQuotient);
Polynomial PolynomialDerivative(Polynomial Poly);
Polynomial PolynomialIndefiniteIntegral(Polynomial Poly);
double PolynomialDefiniteIntegral(Polynomial Poly, int a, int b);

Polynomial InitPolynomial() {
    Polynomial Poly = new PolyNode;
    Poly->next = NULL;
    Polynomial tail = Poly;
    int terms;
    printf("Please enter the number of terms to initialize the polynomial\n");
    scanf("%d", &terms);
    for (int term = 1; term <= terms; term++) {
        Polynomial p = new PolyNode;
        printf(
            "Please enter the coefficient and exponent of the %d term of the "
            "polynomial\n",
            term);
        if (term == 1) {
            printf(
                "Coefficient and exponent should be divided by space, and the "
                "terms should be in descending order\n");
        }
        scanf("%lf%d", &p->coef, &p->exp);
        tail = InsertPolyNode(Poly, p);
    }
    if (Poly->next == NULL) {
        Polynomial p = new PolyNode;
        p->coef = 0;
        p->exp = 0;
        tail->next = p;
        tail = tail->next;
    }
    tail->next = NULL;
    Poly->exp = terms;
    printf("The polynomial: ");
    PrintPolynomial(Poly);
    return Poly;
}

void DestroyPolynomial(Polynomial& Poly) {
    if (Poly == NULL) {
        return;
    }
    Polynomial p = Poly, q = Poly->next;
    while (q) {
        delete p;
        p = q;
        q = q->next;
    }
    Poly = NULL;
}

void PrintPolynomial(Polynomial Poly) {
    if (Poly == NULL || Poly->next == NULL) {
        printf("NULL\n");
        return;
    }
    Polynomial p = Poly->next;
    PrintTerm(p, true);
    p = p->next;
    while (p) {
        PrintTerm(p, false);
        p = p->next;
    }
    printf("\n");
}

void PrintTerm(Polynomial term, bool isFirst) {
    double coef = term->coef;
    int exp = term->exp;
    if (!isFirst && coef > 0) {
        printf("+");
    }
    if (fabs(coef) == 1) {
        if (exp == 1) {
            if (coef == 1) {
                printf("x");
            } else {
                printf("-x");
            }
        } else if (exp == 0) {
            printf("%g", coef);
        } else {
            if (coef > 0) {
                printf("x^%d", exp);
            } else {
                printf("-x^%d", exp);
            }
        }
    } else {
        if (exp == 1) {
            printf("%gx", coef);
        } else if (exp == 0) {
            printf("%g", coef);
        } else {
            printf("%gx^%d", coef, exp);
        }
    }
}

Polynomial CopyPolynomial(Polynomial& Poly) {
    Polynomial PolyNew = new PolyNode;
    *PolyNew = *Poly;
    PolyNew->next = NULL;
    Polynomial tail = PolyNew, p = Poly->next;
    while (p) {
        Polynomial q = new PolyNode;
        *q = *p;
        tail = InsertPolyNode(PolyNew, q);
        p = p->next;
    }
    if (PolyNew->next == NULL) {
        Polynomial p = new PolyNode;
        p->coef = 0;
        p->exp = 0;
        p->next = NULL;
        tail->next = p;
        tail = tail->next;
    }
    tail->next = NULL;
    return PolyNew;
}

Polynomial InsertPolyNode(Polynomial& Poly, Polynomial& node) {
    Polynomial p = Poly, q = Poly->next;
    double nd_coef = node->coef;
    int nd_exp = node->exp;
    while (q && q->exp > nd_exp) {
        p = q;
        q = q->next;
    }
    if (q && q->exp == nd_exp) {
        double sum_coef = q->coef + nd_coef;
        if (sum_coef != 0) {
            q->coef = sum_coef;
        } else {
            p->next = q->next;
            delete q;
            q = NULL;
        }
    } else {
        if (nd_coef != 0) {
            node->next = q;
            p->next = node;
        }
    }
    while (p->next) {
        p = p->next;
    }
    return p;
}

Polynomial PolynomialAddition(Polynomial Poly1, Polynomial Poly2) {
    Polynomial p1 = Poly1->next, p2 = Poly2->next;
    Polynomial Poly = new PolyNode;
    Poly->next = NULL;
    Polynomial tail = Poly;
    while (p1) {
        Polynomial p = new PolyNode;
        *p = *p1;
        tail = InsertPolyNode(Poly, p);
        p1 = p1->next;
    }
    while (p2) {
        Polynomial p = new PolyNode;
        *p = *p2;
        tail = InsertPolyNode(Poly, p);
        p2 = p2->next;
    }
    if (Poly->next == NULL) {
        Polynomial p = new PolyNode;
        p->coef = 0;
        p->exp = 0;
        tail->next = p;
        tail = tail->next;
    }
    tail->next = NULL;
    return Poly;
}

Polynomial PolynomialSubtraction(Polynomial Poly1, Polynomial Poly2) {
    Polynomial p1 = Poly1->next, p2 = Poly2->next;
    Polynomial Poly = new PolyNode;
    Poly->next = NULL;
    Polynomial tail = Poly;
    while (p1) {
        Polynomial p = new PolyNode;
        *p = *p1;
        tail = InsertPolyNode(Poly, p);
        p1 = p1->next;
    }
    while (p2) {
        Polynomial p = new PolyNode;
        *p = *p2;
        p->coef = -1 * p->coef;
        tail = InsertPolyNode(Poly, p);
        p2 = p2->next;
    }
    if (Poly->next == NULL) {
        Polynomial p = new PolyNode;
        p->coef = 0;
        p->exp = 0;
        tail->next = p;
        tail = tail->next;
    }
    tail->next = NULL;
    return Poly;
}

Polynomial PolynomialMultiplication(Polynomial Poly1, Polynomial Poly2) {
    Polynomial p1 = Poly1->next, p2 = Poly2->next;
    Polynomial Poly = new PolyNode;
    Poly->next = NULL;
    Polynomial tail = Poly;
    while (p1) {
        double coef1 = p1->coef;
        int exp1 = p1->exp;
        while (p2) {
            double coef2 = p2->coef;
            int exp2 = p2->exp;
            Polynomial p = new PolyNode;
            p->coef = coef1 * coef2;
            p->exp = exp1 + exp2;
            tail = InsertPolyNode(Poly, p);
            p2 = p2->next;
        }
        p1 = p1->next;
        p2 = Poly2->next;
    }
    if (Poly->next == NULL) {
        Polynomial p = new PolyNode;
        p->coef = 0;
        p->exp = 0;
        tail->next = p;
        tail = tail->next;
    }
    tail->next = NULL;
    return Poly;
}

Polynomial PolynomialDivision(Polynomial Poly1, Polynomial Poly2) {
    Polynomial Poly = CopyPolynomial(Poly1);
    Polynomial PolyNew = new PolyNode;
    PolyNew->next = NULL;
    Polynomial tail = PolyNew;
    while (Poly->next->exp >= Poly2->next->exp) {
        if (Poly->next->coef == 0 && Poly->next->exp == 0) {
            break;
        }
        Polynomial p = new PolyNode, q = new PolyNode;
        p->coef = Poly->next->coef / Poly2->next->coef;
        p->exp = Poly->next->exp - Poly2->next->exp;
        p->next = NULL;
        q->next = p;
        tail = InsertPolyNode(PolyNew, p);
        Poly = PolynomialSubtraction(Poly, PolynomialMultiplication(Poly2, q));
    }
    if (PolyNew->next == NULL) {
        Polynomial p = new PolyNode;
        p->coef = 0;
        p->exp = 0;
        p->next = NULL;
        tail->next = p;
        tail = tail->next;
    }
    if (Poly->next == NULL) {
        Polynomial p = new PolyNode;
        p->coef = 0;
        p->exp = 0;
        p->next = NULL;
        Poly->next = p;
    }
    tail->next = Poly;
    Poly->exp = -1;
    return PolyNew;
}

Polynomial QuotientOrRemainder(Polynomial Poly, bool isQuotient) {
    Polynomial PolyNew = new PolyNode;
    PolyNew->next = NULL;
    Polynomial tail = PolyNew;
    Polynomial p = Poly->next;
    if (isQuotient) {
        while (p && p->exp != -1) {
            Polynomial q = new PolyNode;
            *q = *p;
            p = p->next;
            tail->next = q;
            tail = tail->next;
        }
        tail->next = NULL;
    } else {
        while (p->exp != -1) {
            p = p->next;
        }
        PolyNew = CopyPolynomial(p);
    }
    return PolyNew;
}

Polynomial PolynomialDerivative(Polynomial Poly) {
    Polynomial p = Poly->next;
    Polynomial PolyNew = new PolyNode;
    PolyNew->exp = 0;
    PolyNew->next = NULL;
    Polynomial tail = PolyNew;
    while (p) {
        double coef = p->coef;
        int exp = p->exp;
        if (exp == 0) {
            p = p->next;
            continue;
        }
        Polynomial pNew = new PolyNode;
        pNew->coef = coef * exp;
        pNew->exp = exp - 1;
        tail = InsertPolyNode(PolyNew, pNew);
        p = p->next;
    }
    tail->next = NULL;
    return PolyNew;
}

Polynomial PolynomialIndefiniteIntegral(Polynomial Poly) {
    Polynomial p = Poly->next;
    Polynomial PolyNew = new PolyNode;
    PolyNew->exp = Poly->exp;
    PolyNew->next = NULL;
    Polynomial tail = PolyNew;
    while (p) {
        double coef = p->coef;
        int exp = p->exp;
        Polynomial pNew = new PolyNode;
        pNew->coef = coef / (exp + 1);
        pNew->exp = exp + 1;
        tail->next = pNew;
        tail = tail->next;
        p = p->next;
    }
    tail->next = NULL;
    return PolyNew;
}

double PolynomialDefiniteIntegral(Polynomial Poly, int a, int b) {
    Polynomial PolyIndefInt = PolynomialIndefiniteIntegral(Poly);
    double inf = 0, sup = 0;
    Polynomial pIndefInt = PolyIndefInt->next;
    while (pIndefInt) {
        double coef = pIndefInt->coef;
        int exp = pIndefInt->exp;
        inf += coef * pow(a, exp);
        sup += coef * pow(b, exp);
        pIndefInt = pIndefInt->next;
    }
    return sup - inf;
}

Polynomial GCDPolynomial(Polynomial Poly1, Polynomial Poly2) {
    Polynomial PolyNew1 = CopyPolynomial(Poly1),
               PolyNew2 = CopyPolynomial(Poly2);
    while (true) {
        if (PolyNew1->next->exp < PolyNew2->next->exp) {
            swap(PolyNew1, PolyNew2);
        }
        Polynomial PolyNew = PolynomialDivision(PolyNew1, PolyNew2);
        PolyNew1 = QuotientOrRemainder(PolyNew, false);
        DestroyPolynomial(PolyNew);
        if (PolyNew1 == NULL ||
            (PolyNew1->next->exp == 0 && PolyNew1->next->coef == 0)) {
            return PolyNew2;
        } else if (PolyNew1->next->exp == 0) {
            return PolyNew1;
        }
    }
}

Polynomial LCMPolynomial(Polynomial Poly1, Polynomial Poly2) {
    Polynomial PolyGCD = GCDPolynomial(Poly1, Poly2);
    Polynomial Poly = PolynomialMultiplication(Poly1, Poly2);
    if (PolyGCD->next->exp != 0) {
        Poly = QuotientOrRemainder(PolynomialDivision(Poly, PolyGCD), true);
    }
    return Poly;
}
int main() {
    int option;
    Polynomial polynomial1 = NULL, polynomial2 = NULL, polynomialAns = NULL;
    while (true) {
        printf("---------------------\n");
        printf("1.Create polynomial\n");
        printf("2.Delete polynomial\n");
        printf("3.Print polynomials\n");
        printf("4.The four operations\n");
        printf("5.Calculus\n");
        printf("6.GCP and LCP\n");
        printf("0.Exit\n");
        printf("---------------------\n");
        scanf("%d", &option);
        switch (option) {
            case 1: {
                int option1;
                printf("The storage:\n");
                printf("1.f(x)=");
                PrintPolynomial(polynomial1);
                printf("2.g(x)=");
                PrintPolynomial(polynomial2);
                printf("Please enter the polynomial you want to create\n");
                scanf("%d", &option1);
                if (option1 == 1) {
                    DestroyPolynomial(polynomial1);
                    polynomial1 = InitPolynomial();
                } else if (option1 == 2) {
                    DestroyPolynomial(polynomial2);
                    polynomial2 = InitPolynomial();
                } else {
                    printf("Invalid input\n");
                }
                break;
            }
            case 2: {
                int option2;
                printf("Please enter the polynomial you want to delete\n");
                scanf("%d", &option2);
                if (option2 == 1) {
                    DestroyPolynomial(polynomial1);
                    printf("f(x) is deleted");
                } else if (option2 == 2) {
                    DestroyPolynomial(polynomial2);
                    printf("g(x) is deleted");
                } else {
                    printf("Invalid input\n");
                }
                printf("The storage\n");
                printf("f(x)=");
                PrintPolynomial(polynomial1);
                printf("g(x)=");
                PrintPolynomial(polynomial2);
                break;
            }
            case 3: {
                printf("f(x)=");
                PrintPolynomial(polynomial1);
                printf("g(x)=");
                PrintPolynomial(polynomial2);
                break;
            }
            case 4: {
                int option4;
                printf("----------------\n");
                printf("1.Addtion\n");
                printf("2.Subtraction\n");
                printf("3.Multiplication\n");
                printf("4.Division\n");
                printf("----------------\n");
                scanf("%d", &option4);
                switch (option4) {
                    case 1: {
                        if (polynomial1 && polynomial2) {
                            if (polynomialAns) {
                                DestroyPolynomial(polynomialAns);
                            }
                            polynomialAns =
                                PolynomialAddition(polynomial1, polynomial2);
                            printf("f(x)=");
                            PrintPolynomial(polynomial1);
                            printf("g(x)=");
                            PrintPolynomial(polynomial2);
                            printf("Ans=f+g=");
                            PrintPolynomial(polynomialAns);
                        } else {
                            printf("Invalid addtion\n");
                            printf("Please check your polynomials:\n");
                            printf("f(x)=");
                            PrintPolynomial(polynomial1);
                            printf("g(x)=");
                            PrintPolynomial(polynomial2);
                        }
                        break;
                    }
                    case 2: {
                        if (polynomial1 && polynomial2) {
                            if (polynomialAns) {
                                DestroyPolynomial(polynomialAns);
                            }
                            polynomialAns =
                                PolynomialSubtraction(polynomial1, polynomial2);
                            printf("f(x)=");
                            PrintPolynomial(polynomial1);
                            printf("g(x)=");
                            PrintPolynomial(polynomial2);
                            printf("Ans=f-g=");
                            PrintPolynomial(polynomialAns);
                        } else {
                            printf("Invalid subtraction\n");
                            printf("Please check your polynomials:\n");
                            printf("f(x)=");
                            PrintPolynomial(polynomial1);
                            printf("g(x)=");
                            PrintPolynomial(polynomial2);
                        }
                        break;
                    }
                    case 3: {
                        if (polynomial1 && polynomial2) {
                            if (polynomialAns) {
                                DestroyPolynomial(polynomialAns);
                            }
                            polynomialAns = PolynomialMultiplication(
                                polynomial1, polynomial2);
                            printf("f(x)=");
                            PrintPolynomial(polynomial1);
                            printf("g(x)=");
                            PrintPolynomial(polynomial2);
                            printf("Ans=f*g=");
                            PrintPolynomial(polynomialAns);
                        } else {
                            printf("Invalid multiplication\n");
                            printf("Please check your polynomials:\n");
                            printf("f(x)=");
                            PrintPolynomial(polynomial1);
                            printf("g(x)=");
                            PrintPolynomial(polynomial2);
                        }
                        break;
                    }
                    case 4: {
                        if (polynomial1 && polynomial2 &&
                            polynomial2->next->coef != 0) {
                            if (polynomialAns) {
                                DestroyPolynomial(polynomialAns);
                            }
                            polynomialAns =
                                PolynomialDivision(polynomial1, polynomial2);
                            printf("f(x)=");
                            PrintPolynomial(polynomial1);
                            printf("g(x)=");
                            PrintPolynomial(polynomial2);
                            printf("Quotient=");
                            PrintPolynomial(
                                QuotientOrRemainder(polynomialAns, true));
                            printf("Remainder=");
                            PrintPolynomial(
                                QuotientOrRemainder(polynomialAns, false));

                        } else {
                            printf("Invalid division\n");
                            printf("Please check your polynomials:\n");
                            printf("f(x)=");
                            PrintPolynomial(polynomial1);
                            printf("g(x)=");
                            PrintPolynomial(polynomial2);
                        }
                        break;
                    }
                }
                break;
            }
            case 5: {
                int option5;
                printf("----------------\n");
                printf("1.Derivative\n");
                printf("2.Indefinite integral\n");
                printf("3.Definite integral\n");
                printf("----------------\n");
                scanf("%d", &option5);
                switch (option5) {
                    case 1: {
                        int option5_1;
                        printf(
                            "Please enter the name of the polynomial you "
                            "want "
                            "to find the indefinite integral\n");
                        scanf("%d", &option5_1);
                        if (polynomial1 && option5_1 == 1) {
                            if (polynomialAns) {
                                DestroyPolynomial(polynomialAns);
                            }
                            polynomialAns = PolynomialDerivative(polynomial1);
                            printf("h(x)=");
                            PrintPolynomial(polynomialAns);
                        } else if (polynomial2 && option5_1 == 2) {
                            if (polynomialAns) {
                                DestroyPolynomial(polynomialAns);
                            }
                            polynomialAns = PolynomialDerivative(polynomial2);
                            printf("h(x)=");
                            PrintPolynomial(polynomialAns);
                        } else {
                            printf("Polynomial not found\n");
                        }
                        break;
                    }
                    case 2: {
                        int option5_2;
                        printf(
                            "Please enter the name of the polynomial you "
                            "want "
                            "to find the indefinite integral\n");
                        scanf("%d", &option5_2);
                        if (polynomial1 && option5_2 == 1) {
                            if (polynomialAns) {
                                DestroyPolynomial(polynomialAns);
                            }
                            polynomialAns =
                                PolynomialIndefiniteIntegral(polynomial1);
                            printf("h(x)=");
                            PrintPolynomial(polynomialAns);
                        } else if (polynomial2 && option5_2 == 2) {
                            if (polynomialAns) {
                                DestroyPolynomial(polynomialAns);
                            }
                            polynomialAns =
                                PolynomialIndefiniteIntegral(polynomial2);
                            printf("h(x)=");
                            PrintPolynomial(polynomialAns);
                        } else {
                            printf("Polynomial not found\n");
                        }
                        break;
                    }
                    case 3: {
                        int option5_3;
                        double lower_bound, upper_bound;
                        double ans;
                        printf(
                            "Please enter the name of the polynomial you "
                            "want "
                            "to find the definite integral\n");
                        scanf("%d", &option5_3);
                        printf(
                            "Please enter the bounds of the polynomial, "
                            "with "
                            "lower bound and upper bound divided by "
                            "space\n");
                        scanf("%lf%lf", &lower_bound, &upper_bound);
                        if (polynomial1 && option5_3 == 1) {
                            if (polynomialAns) {
                                DestroyPolynomial(polynomialAns);
                            }
                            ans = PolynomialDefiniteIntegral(
                                polynomial1, lower_bound, upper_bound);
                            printf("Ans = %g\n", ans);
                        } else if (polynomial2 && option5_3 == 2) {
                            if (polynomialAns) {
                                DestroyPolynomial(polynomialAns);
                            }
                            ans = PolynomialDefiniteIntegral(
                                polynomial2, lower_bound, upper_bound);
                            printf("Ans = %g\n", ans);
                        } else {
                            printf("Polynomial not found\n");
                        }
                        break;
                    }
                }
                break;
            }
            case 6: {
                int option6;
                printf("-----\n");
                printf("1.GCD\n");
                printf("2.LCM\n");
                printf("-----\n");
                scanf("%d", &option6);
                switch (option6) {
                    case 1: {
                        if (polynomial1 && polynomial2) {
                            if (polynomialAns) {
                                DestroyPolynomial(polynomialAns);
                            }
                            polynomialAns =
                                GCDPolynomial(polynomial1, polynomial2);
                            printf("f(x)=");
                            PrintPolynomial(polynomial1);
                            printf("g(x)=");
                            PrintPolynomial(polynomial2);
                            printf("GCD(f, g)=");
                            PrintPolynomial(polynomialAns);
                        } else {
                            printf("Invalid operation\n");
                            printf("Please check your polynomials:\n");
                            printf("f(x)=");
                            PrintPolynomial(polynomial1);
                            printf("g(x)=");
                            PrintPolynomial(polynomial2);
                        }
                        break;
                    }
                    case 2: {
                        if (polynomial1 && polynomial2) {
                            if (polynomialAns) {
                                DestroyPolynomial(polynomialAns);
                            }
                            polynomialAns =
                                LCMPolynomial(polynomial1, polynomial2);
                            printf("f(x)=");
                            PrintPolynomial(polynomial1);
                            printf("g(x)=");
                            PrintPolynomial(polynomial2);
                            printf("LCM(f, g)=");
                            PrintPolynomial(polynomialAns);
                        } else {
                            printf("Invalid operation\n");
                            printf("Please check your polynomials:\n");
                            printf("f(x)=");
                            PrintPolynomial(polynomial1);
                            printf("g(x)=");
                            PrintPolynomial(polynomial2);
                        }
                        break;
                    }
                }
                break;
            }
            case 0: {
                exit(0);
                break;
            }
            default: {
                break;
            }
        }
    }

    return 0;
}