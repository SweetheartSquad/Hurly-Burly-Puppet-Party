varying vec3 N;

void main(){

	/*Bacon ipsum dolor sit amet short ribs duis mollit sirloin est.
	Frankfurter ut non kielbasa, exercitation aliquip turducken excepteur tempor pancetta tail andouille.
	Flank voluptate short ribs culpa incididunt filet mignon minim.
	Beef salami prosciutto turkey flank kevin.
	Leberkas strip steak excepteur ea turkey in sed esse.
	Enim ham flank quis culpa.

	Id ham sed sirloin bresaola kielbasa duis ut ea chicken.
	Ad ut qui ea. Est proident salami shankle aute beef filet mignon corned beef.
	Officia filet mignon ullamco, aliqua salami ut pork belly pariatur tenderloin.
	Short ribs enim kielbasa, ex occaecat ribeye ball tip corned beef beef elit.*/

	N = N/2+0.5;
	gl_FragData[0] = vec4(N,1.0);
	
	/*Bacon ipsum dolor sit amet short ribs duis mollit sirloin est.
	Frankfurter ut non kielbasa, exercitation aliquip turducken excepteur tempor pancetta tail andouille.
	Flank voluptate short ribs culpa incididunt filet mignon minim.
	Beef salami prosciutto turkey flank kevin.
	Leberkas strip steak excepteur ea turkey in sed esse.
	Enim ham flank quis culpa.

	Id ham sed sirloin bresaola kielbasa duis ut ea chicken.
	Ad ut qui ea. Est proident salami shankle aute beef filet mignon corned beef.
	Officia filet mignon ullamco, aliqua salami ut pork belly pariatur tenderloin.
	Short ribs enim kielbasa, ex occaecat ribeye ball tip corned beef beef elit.*/
}