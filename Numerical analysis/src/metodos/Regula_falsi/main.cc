/*
* Autor: Matias Greco
*		 Juan-pablo Barahona
* Date: 21/09/2015
*/

#include "../../fparser4.5.2/fparser.hh"
#include "../../INCLUDE/raiz.hh"

int main()
{
	double ReglaFalsa(FunctionParser fparser,double xi, double xf, double errto,double imax, std::ostream& of);

	std::string function;
	double xi,xf,errto,imax;
	
	//===================================================================
	//================= Leer parametros desde input.txt =================
	
	std::string line;
	char * fx = new char [25];
	std::ifstream fe ("inputs/input.txt");
	int i = 0,j;
	if (fe == NULL) perror ("Error abrir archivo");
	else
	{
		while(getline (fe,line))
		{	
			char * cstr = new char [line.length()+1];
			std::strcpy (cstr, line.c_str());
		 	if(line.compare(0,7,"F(x) = ") == 0)
		 	{
				j = 0;i = 7;
				
				do
				{
					fx[j] = cstr[i];
					i++;j++;
				}while(cstr[i] != '\0');
				
				std::string sfx(fx);
				function = sfx;
			}
			if(line.compare(0,5,"xi = ") == 0)
		 	{
				xi = dvalue(5,cstr);
			}
			if(line.compare(0,5,"xf = ") == 0)
		 	{
				xf = dvalue(5,cstr);
			}
			if(line.compare(0,8,"errto = ") == 0)
		 	{
				errto = dvalue(8,cstr);
			}
			if(line.compare(0,7,"imax = ") == 0)
		 	{
				imax = dvalue(7,cstr);
			}
		}
	}
	
	fe.close();
	
	//================================================================
	
    FunctionParser fparser;

    fparser.AddConstant("pi", 3.1415926535897932);
    fparser.AddConstant("e", 2.718281828);

    while(true)
    {
        int res = fparser.Parse(function, "x");
        if(res < 0) break;

        std::cout << std::string(res+7, ' ') << "^\n"
                  << fparser.ErrorMsg() << "\n\n";
    }
    
    char * file = fichero("out", "cc", "er", "rf","out","txt",100);

    std::ofstream of(file);

    of << "\nf(x) =" << function << "\n"
	   << "Xi = " << xi << "\n"
	   << "Xf = " << xf << "\n"
	   << "errto = " << errto << "\n"
	   << "imax = " << imax << "\n\n";

	of << "\n" << "Numero de" << "\n" << "Iteracion" 
       << std::setw(14) << "Xi" 
       << std::setw(16) << "Xf"
       << std::setw(16) << "Raiz"
       << std::setw(20) << "Error" 
       << std::setw(20) << "Tolerancia" 
       << std::setw(18) << "f(Raiz)\n" << std::endl;

	double raiz = ReglaFalsa(fparser, xi, xf, errto, imax,of);
	of << "\n" << "La raíz aproximada es: "<< raiz << "\n" << std::endl;
	of.close();
	free(file);
}

double ReglaFalsa(FunctionParser fparser,double xi, double xf, double errto,double imax, std::ostream& of)
{
	/*
	 *	xi: inicio intervalo
	 *	xf: fin intervalo
	 *	xr: raiz (en esa iteracion)
	 *	errto (porcentaje de error maximo, como criterio de paro)
	*/

    int iteracion = 0;
    double xr = 0, error = errto + 1, anterior;

    double fxi,fxf,fxr;

    while (error > errto && iteracion < imax) {
        anterior = xr;
        fxf = f(fparser,xf);
        fxi = f(fparser,xi);

        xr = xf -((fxf*(xi-xf)))/(fxi-fxf);

        fxr = f(fparser,xr);

        //error = (sqrt((xr-anterior)*(xr-anterior)))/xr;
        error = fabs((xr - anterior)/xr) * 100;  // pagina 100 del libro (criterio de paro)
        iteracion++;

        of << "  " << std::setw(2) << iteracion
		   << "  " << std::setw(16) << xi
		   << "  " << std::setw(16) << xf
		   << "  |" << std::setw(16) << std::setprecision(14) << xr
		   << "  " << std::setw(20) << error 
		   << "  " << std::setw(8) << errto 
		   << "  " << std::setw(22) << fxr << std::endl;

        if(fxi*fxr < 0)
           xf = xr;
       	else
           xi = xr;
    }

    return xr;

}