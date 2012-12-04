/* Spextral unmixing with Singular Value Decomposition */
/* (c) 15. Jan. 1999 Markus Neteler, Hannover*/

/* Cited references are from
     Steward, D.E, Leyk, Z. 1994: Meschach: Matrix computations in C.
        Proceedings of the centre for Mathematics and its Applicaions.
        The Australian National University. Vol. 32.
        ISBN 0 7315 1900 0
*/

#include <stdio.h>
#include <math.h>
#include <grass/imagery.h>
#include <grass/gmath.h>
#include <grass/glocale.h>
#include "global.h"


int open_files (char *matrixfile,
                char *img_grp,
                char *iter_name,
                char *error_name,
                mat_struct *A)
{
    char result_name[80];
    char *result_prefix="out";
    FILE *fp;
    int i, matrixsize;
    mat_struct A_input;
  
    
//     mat_struct A_input1;
/*

    if ((fp = fopen (matrixfile, "r")) == NULL)
    	 G_fatal_error (_("Matrix file %s not found."), matrixfile);
    	 
    	 
   //G_matrix_init2( &A_input,3,3,3);
   // G_warning("matrix read start");
//    G_warning("cols=%d",A_input->cols);

    if ((G_matrix_read (fp, &A_input) < 0))
        G_fatal_error (_("Unable to read matrix file %s."), matrixfile);
    fclose (fp);

    //G_matrix_print(&A_input);


  // G_warning("matrix read done");
#if 0
    G_message(_("Your spectral matrix = %d"), m_output(A_input));
#endif



//    A = m_get(A_input->rows, A_input->cols);

    G_matrix_clone2(&A_input, A);
  

    
    //*A = *G_matrix_init (A_input.rows, A_input.cols, A_input.rows);
//    if (A == NULL)
      //  G_fatal_error (_("Unable to allocate memory for matrix"));

    A = G_matrix_transpose (&A_input);
    
   // G_matrix_free (&A_input);

//     G_matrix_print(A);   

    if ((A->rows) < (A->cols))
	G_fatal_error (_("Need number of cols >= rows to perform least squares fitting."));

    // number of rows must be equivalent to no. of bands
    matrixsize = A->cols;

    // open input files from group
    if (!I_find_group (img_grp))
	G_fatal_error (_("Unable to find imagery group %s."), img_grp);

    I_get_group_ref (img_grp, &Ref);
    if (Ref.nfiles <= 1)
    {
	if (Ref.nfiles <= 0)
            G_fatal_error (_("Group %s does not have any rasters. "
                        "The group must have at least 2 rasters."), img_grp);
	else
            G_fatal_error (_("Group %s only has 1 raster. "
                        "The group must have at least 2 rasters."), img_grp);
    }

    // Error check: input file number must be equal to matrix size
    if (Ref.nfiles != matrixsize)
        G_fatal_error (_("Number of input files (%i) in group <%s> "
                    "does not match number of spectra in matrix. "
                    "(contains only %i cols)."),
                    Ref.nfiles, img_grp, A->cols);

    // get memory for input files
    cell = (CELL **) G_malloc (Ref.nfiles * sizeof (CELL *));
    cellfd = (int *) G_malloc (Ref.nfiles * sizeof (int));
    for (i = 0; i < Ref.nfiles; i++)
    {
	cell[i] = Rast_allocate_c_buf();

	G_message (_("Opening input file no. %i [%s]"), (i + 1), Ref.file[i].name);

	if ((cellfd[i] = Rast_open_old  (Ref.file[i].name, Ref.file[i].mapset)) < 0)
	    G_fatal_error (_("Unable to open <%s>"), Ref.file[i].name);
    }

    // open files for results 
    result_cell = (CELL **) G_malloc (Ref.nfiles * sizeof (CELL *));
    resultfd = (int *) G_malloc (Ref.nfiles * sizeof (int));

    for (i = 0; i < A->cols; i++)      // no. of spectra
    {
	 sprintf (result_name, "%s.%d", result_prefix, (i + 1));
         G_message (_("Opening output file [%s]"), result_name);

	 result_cell[i] = Rast_allocate_c_buf();
	 if ((resultfd[i] = Rast_open_c_new (result_name)) < 0)
	 	G_fatal_error (_("GRASS-DB internal error: Unable to proceed."));
    }

    // open file containing SMA error
    error_cell = (CELL *) G_malloc (sizeof(CELL *));
    if (error_name)
    {
        G_message (_("Opening error file [%s]"), error_name);

        if ((error_fd = Rast_open_c_new (error_name)) < 0)
            G_fatal_error (_("Unable to create error layer [%s]"), error_name);
        else
            error_cell = Rast_allocate_c_buf();
    }

    // open file containing number of iterations 
    iter_cell = (CELL *) G_malloc (sizeof(CELL *));
    if (iter_name)
    {
	G_message (_("Opening iteration file [%s]"), iter_name);

        if ((iter_fd = Rast_open_c_new (iter_name)) < 0)
	    G_fatal_error (_("Unable to create iterations layer [%s]"), iter_name);
	else
	    iter_cell = Rast_allocate_c_buf();
    }

 //G_matrix_print(A); 

    return matrixsize;
    */
    return 0;
}








mat_struct* open_files2 (char *matrixfile,
                char *img_grp,
                char *result_prefix,                
                char *iter_name,
                char *error_name)
{
    char result_name[80];

    FILE *fp;
    int i, matrixsize;
    mat_struct A_input, *A;
  
    
//     mat_struct A_input1;
    
    
    /* Read in matrix file with spectral library.
     * Input matrix must contain spectra row-wise (for user's convenience)!
     * Transposed here to col-wise orientation (for modules/mathematical 
     * convenience). */

    if ((fp = fopen (matrixfile, "r")) == NULL)
    	 G_fatal_error (_("Matrix file %s not found."), matrixfile);
    	 
    	 
   //G_matrix_init2( &A_input,3,3,3);
   // G_warning("matrix read start");
//    G_warning("cols=%d",A_input->cols);
    /* Read data and close file */
    if ((G_matrix_read2 (fp, &A_input) < 0))
        G_fatal_error (_("Unable to read matrix file %s."), matrixfile);
    fclose (fp);

    //G_matrix_print2(&A_input, "A_input");


  // G_warning("matrix read done");
#if 0
    G_message(_("Your spectral matrix = %d"), m_output(A_input));
#endif

    /* transpose input matrix from row orientation to col orientation.
     * Don't mix rows and cols in the source code and the modules
     * messages output! */

//    A = m_get(A_input->rows, A_input->cols);

    //G_matrix_clone2(&A_input, A);
  

    
    A = G_matrix_init (A_input.rows, A_input.cols, A_input.rows);
    if (A == NULL)
        G_fatal_error (_("Unable to allocate memory for matrix"));

    A = G_matrix_transpose (&A_input);
    
   // G_matrix_free (&A_input);

//     G_matrix_print(A);   

    if ((A->rows) < (A->cols))
	G_fatal_error (_("Need number of cols >= rows to perform least squares fitting."));

    // number of rows must be equivalent to no. of bands
    matrixsize = A->rows;

    // open input files from group
    if (!I_find_group (img_grp))
	G_fatal_error (_("Unable to find imagery group %s."), img_grp);

    I_get_group_ref (img_grp, &Ref);
    if (Ref.nfiles <= 1)
    {
	if (Ref.nfiles <= 0)
            G_fatal_error (_("Group %s does not have any rasters. "
                        "The group must have at least 2 rasters."), img_grp);
	else
            G_fatal_error (_("Group %s only has 1 raster. "
                        "The group must have at least 2 rasters."), img_grp);
    }

    // Error check: input file number must be equal to matrix size
    if (Ref.nfiles != matrixsize)
        G_fatal_error (_("Number of input files (%i) in group <%s> "
                    "does not match number of spectra in matrix. "
                    "(contains %i cols)."),
                    Ref.nfiles, img_grp, A->rows);

    // get memory for input files
    cell = (CELL **) G_malloc (Ref.nfiles * sizeof (CELL *));
    cellfd = (int *) G_malloc (Ref.nfiles * sizeof (int));
    for (i = 0; i < Ref.nfiles; i++)
    {
	cell[i] = Rast_allocate_c_buf();

	G_message (_("Opening input file no. %i [%s]"), (i + 1), Ref.file[i].name);

	if ((cellfd[i] = Rast_open_old  (Ref.file[i].name, Ref.file[i].mapset)) < 0)
	    G_fatal_error (_("Unable to open <%s>"), Ref.file[i].name);

    
    }
    
 

    // open files for results 
    result_cell = (CELL **) G_malloc (Ref.nfiles * sizeof (CELL *));
    resultfd = (int *) G_malloc (Ref.nfiles * sizeof (int));

    for (i = 0; i < A->cols; i++)      // no. of spectra
    {
      if (result_prefix)
      {
	      sprintf (result_name, "%s.%d", result_prefix, (i + 1));
        G_message (_("Opening output file [%s]"), result_name);

	      result_cell[i] = Rast_allocate_c_buf();
	      if ((resultfd[i] = Rast_open_c_new (result_name)) < 0)
	 	      G_fatal_error (_("GRASS-DB internal error: Unable to proceed."));
      }
    }
    // open file containing SMA error
    error_cell = (CELL *) G_malloc (sizeof(CELL *));
    if (error_name)
    {
        G_message (_("Opening error file [%s]"), error_name);

        if ((error_fd = Rast_open_c_new (error_name)) < 0)
            G_fatal_error (_("Unable to create error layer [%s]"), error_name);
        else
            error_cell = Rast_allocate_c_buf();
    }

    // open file containing number of iterations 
    iter_cell = (CELL *) G_malloc (sizeof(CELL *));
    if (iter_name)
    {
	G_message (_("Opening iteration file [%s]"), iter_name);

        if ((iter_fd = Rast_open_c_new (iter_name)) < 0)
	    G_fatal_error (_("Unable to create iterations layer [%s]"), iter_name);
	else
	    iter_cell = Rast_allocate_c_buf();
    }



    /* give back number of output files (= Ref.nfiles) */
    return A;
}
