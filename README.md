# SUPERNOVA - a static webpage generator 

Supernova is a lightweight, fast HTML generator powered by a custom domain-specific 
language (DSL). Designed for creators and developers, it lets you write clean, structured
content with minimal boilerplate. 

This is a personal project that I use to build my static pages. So this is customized to my usecases.


> [!WARNING]  
> Lexer under construction.



### SUPERDOWN STRUCTURES

1. @(props)  sub_title
2. @(props)  main_title
3. @(props)  title
4. @(props)  description
5. @(props)  link
6. @(props)  code
7. @(props)  h1 
8. @(props)  h2 
9. @(props)  h3 
10. @(props)  h4 
11. @(props)  h5 
12. @(props)  h6 
13. @(props)  inject
14. @(props)  enclose


## WORKING

The compiler will generate HTML sequentially so the order or structure defined in `.supd` matter

## IMPLEMENTATION

@("custom-class1 custom-class2", "custom id", "styles")main_title {main title}
@sub_title {sub title}
@title {title}
@description {paragraph}
@link {link}
@injext {custom html}



## Page structure

```html
<page>
<main_body>
<main_title></main_title>
<sub_heading></sub_heading>
...
<sub_heading></sub_heading>
<footer></footer>
</main_body>
<page>
```
