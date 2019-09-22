#include "nodoabb.h"

nodoabb::nodoabb(string n, int dh, int dw, int ph, int pw, listacapas *l)
{
    nombre = n;
    dimH = dh;
    dimW = dw;
    pixH = ph;
    pixW = pw;
    listaC = l;
    fr = 51;
    fg = 51;
    fb = 51;
    ni = NULL;
    nd = NULL;
}

void nodoabb::generar2()
{
    string ins = "mkdir Exports/" + nombre;
    system(ins.c_str());
    //listaC->graficar_capas();
    listaC->linealizar2();
    //listaC->todo->graficar(listaC->todo->capa,nombre);
    //listaC->linealizada->graficar();

    FILE *html;
    FILE *scss;
    string rHTML = "Exports/" + nombre + "/" + nombre + ".html";
    string rSCSS = "Exports/" + nombre + "/" + nombre + ".scss";
    html = fopen(rHTML.c_str(),"w+");
    scss = fopen(rSCSS.c_str(),"w+");
    if((html) && (scss))
    {
        //
        //html
        fprintf(html,"<!DOCTYPE html>\r\n");
        fprintf(html,"<html>\r\n");
        fprintf(html,"<head>\r\n");
        fprintf(html,"\t<link rel=\"stylesheet\" href=\"%s.scss\">\r\n",nombre.c_str());
        fprintf(html,"</head>\r\n");
        fprintf(html,"<body>\r\n");
        fprintf(html,"<div class=\"canvas\">\r\n");
        //
        //scss
        fprintf(scss,"body {\r\n");
        fprintf(scss,"\tbackground: %s;\r\n",listaC->todo->rgb_h(fr,fg,fb).c_str());
        fprintf(scss,"\theight: 100vh;\r\n");
        fprintf(scss,"\tdisplay: flex;\r\n");
        fprintf(scss,"\tjustify-content: center;\r\n");
        fprintf(scss,"\talign-items: center;\r\n");
        fprintf(scss,"}\r\n");
        //
        fprintf(scss,".canvas {\r\n");
        if(listaC->linealizada->totC == dimW)
        {
            fprintf(scss,"\twidth: %ipx;\r\n",dimW*pixW);
        } else 
        {
            fprintf(scss,"\twidth: %ipx;\r\n",listaC->linealizada->totC*pixW);
        }
        if(listaC->linealizada->totF == dimH)
        {
            fprintf(scss,"\theight: %ipx;\r\n",dimH*pixH);
        } else 
        {
            fprintf(scss,"\theight: %ipx;\r\n",listaC->linealizada->totF*pixH);
        }
        fprintf(scss,"}\r\n");
        //
        fprintf(scss,".pixel {\r\n");
        fprintf(scss,"\twidth: %ipx;\r\n",pixW);
        fprintf(scss,"\theight: %ipx;\r\n",pixH);
        fprintf(scss,"\tfloat: left;\r\n");
        fprintf(scss,"\tbox-shadow: 0px 0px 1px #fff;\r\n");
        fprintf(scss,"}\r\n");
        
        //
        //RECORRIDO
        //
        int cn = 1;
        nodolineal *aux = listaC->linealizada->primero;
        while(aux != NULL)
        {
            fprintf(html,"\t<div class=\"pixel\"></div>\r\n");
            if(aux->colorH != "//")
            {
                fprintf(scss,".pixel:nth-child(%i) { background: %s }\r\n",cn,aux->colorH.c_str());
            } else
            {
                fprintf(scss,".pixel:nth-child(%i) { background: %s }\r\n",cn,listaC->todo->rgb_h(fr,fg,fb).c_str());
            }
            cn++;
            aux = aux->sig;
        }
        
        //
        //html
        fprintf(html,"</div>\r\n");
        fprintf(html,"</body>\r\n");
        fprintf(html,"</html>\r\n");
    }
    fclose(html);
    fclose(scss);
    string op = "xdg-open " + rHTML;
    system(op.c_str());
}

void nodoabb::generar()
{
    string ins = "mkdir Exports/" + nombre;
    system(ins.c_str());
    //listaC->graficar_capas();
    listaC->linealizar();
    //listaC->todo->graficar(listaC->todo->capa,nombre);
    //listaC->linealizada->graficar();

    FILE *html;
    FILE *scss;
    string rHTML = "Exports/" + nombre + "/" + nombre + ".html";
    string rSCSS = "Exports/" + nombre + "/" + nombre + ".scss";
    html = fopen(rHTML.c_str(),"w+");
    scss = fopen(rSCSS.c_str(),"w+");
    if((html) && (scss))
    {
        //
        //html
        fprintf(html,"<!DOCTYPE html>\r\n");
        fprintf(html,"<html>\r\n");
        fprintf(html,"<head>\r\n");
        fprintf(html,"\t<link rel=\"stylesheet\" href=\"%s.scss\">\r\n",nombre.c_str());
        fprintf(html,"</head>\r\n");
        fprintf(html,"<body>\r\n");
        fprintf(html,"<div class=\"canvas\">\r\n");
        //
        //scss
        fprintf(scss,"body {\r\n");
        fprintf(scss,"\tbackground: %s;\r\n",listaC->todo->rgb_h(fr,fg,fb).c_str());
        fprintf(scss,"\theight: 100vh;\r\n");
        fprintf(scss,"\tdisplay: flex;\r\n");
        fprintf(scss,"\tjustify-content: center;\r\n");
        fprintf(scss,"\talign-items: center;\r\n");
        fprintf(scss,"}\r\n");
        //
        fprintf(scss,".canvas {\r\n");
        if(listaC->linealizada->totC == dimW)
        {
            fprintf(scss,"\twidth: %ipx;\r\n",dimW*pixW);
        } else 
        {
            fprintf(scss,"\twidth: %ipx;\r\n",listaC->linealizada->totC*pixW);
        }
        if(listaC->linealizada->totF == dimH)
        {
            fprintf(scss,"\theight: %ipx;\r\n",dimH*pixH);
        } else 
        {
            fprintf(scss,"\theight: %ipx;\r\n",listaC->linealizada->totF*pixH);
        }
        fprintf(scss,"}\r\n");
        //
        fprintf(scss,".pixel {\r\n");
        fprintf(scss,"\twidth: %ipx;\r\n",pixW);
        fprintf(scss,"\theight: %ipx;\r\n",pixH);
        fprintf(scss,"\tfloat: left;\r\n");
        fprintf(scss,"\tbox-shadow: 0px 0px 1px #fff;\r\n");
        fprintf(scss,"}\r\n");
        
        //
        //RECORRIDO
        //
        int cn = 1;
        nodolineal *aux = listaC->linealizada->primero;
        while(aux != NULL)
        {
            fprintf(html,"\t<div class=\"pixel\"></div>\r\n");
            if(aux->colorH != "//")
            {
                fprintf(scss,".pixel:nth-child(%i) { background: %s }\r\n",cn,aux->colorH.c_str());
            } else
            {
                fprintf(scss,".pixel:nth-child(%i) { background: %s }\r\n",cn,listaC->todo->rgb_h(fr,fg,fb).c_str());
            }
            cn++;
            aux = aux->sig;
        }
        
        //
        //html
        fprintf(html,"</div>\r\n");
        fprintf(html,"</body>\r\n");
        fprintf(html,"</html>\r\n");
    }
    fclose(html);
    fclose(scss);
    string op = "xdg-open " + rHTML;
    system(op.c_str());
}