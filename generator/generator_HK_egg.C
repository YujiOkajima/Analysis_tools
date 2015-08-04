#include<fstream>
#include<iostream>
#include<math.h>

void generator_HK_egg(int partition=5, double energy, int particle, int neutrino, double mass){
  //partition: partition number of detector
  //energy: kinetic energy
  //particle: particle ID of target particle                                                                                                                   
  //neutrino: neutrino which is interacted with target particle                                                                                                
  //mass mass of target particle      

  TRandom random(0);
  char filename[100];
  double zmax;
  double r2max;
  double vertex[3];
  double dir[3];
  double nev;
  double phi;
	
  double xmax=1909.5;
  double ymax=1909.5;
  double rmax=1909.5;
  zmax=(24750/partition-100)/2-200;


		for(int j=1;j<=1;j++){
		  sprintf(filename,"eventlist_HKegg_particle%d_%dMeV_%dpart.txt",particle,(int)energy,partition);
		  ofstream ofs(filename);

		    for(nev=0;nev<10000;nev++){
		      vertex[1]=ymax*(2*random.Rndm()-1);
		      vertex[0]=xmax*(2*random.Rndm()-1);
		      vertex[2]=zmax*(2*random.Rndm()-1);

		      while(fabs(vertex[1])>ymax||(vertex[1]>0&&pow(fabs(vertex[0])+800,2)+vertex[1]*vertex[1]>(rmax+800)*(rmax+800))||(vertex[1]<0&&pow(fabs(vertex[0])+600,2)+vertex[1]*vertex[1]>(rmax+600)*(rmax+600))){
		      vertex[1]=ymax*(2*random.Rndm()-1);
		      vertex[0]=xmax*(2*random.Rndm()-1);
		      vertex[2]=zmax*(2*random.Rndm()-1);
		    }
		      phi=6.283185307*random.Rndm();
		      dir[2]=2*random.Rndm()-1;
		      dir[1]=sqrt(1-dir[2]*dir[2]);
		      dir[0]=dir[1]*cos(phi);
		      dir[1]*=sin(phi);

		      double momentum = sqrt((energy+mass)*(energy+mass)-mass*mass);
		      double totalenergy=(mass+momentum+sqrt(mass*mass+momentum*momentum))/2;
				

				ofs << "$begin" << std::endl;
				ofs << "$neut 3" << std::endl;
				ofs << "$vertex " << vertex[0] << " " << vertex[1] << " " << vertex[2] << " dummy" << std::endl;
				ofs << "$track " << particle << " " << mass << " 0 0 0 -1" << std::endl;
				ofs << "$track " << neutrino << " "  << totalenergy-mass << " " << dir[0] << " " << dir[1] << " " << dir[2] << " " << "-1" << std::endl;
				ofs << "$info event " << nev+1 << std::endl;
				ofs << "$track " << particle << " " << energy+mass << " " << dir[0] << " " << dir[1] << " " << dir[2] << " " << "-2" << std::endl;
				ofs << "$track " << neutrino << " "  << totalenergy-sqrt(momentum*momentum+mass*mass) << " " << -dir[0] << " " << -dir[1] << " " << -dir[2] << " " << "-2" << std::endl;
				ofs << "$track " << particle << " " << energy+mass << " " << dir[0] << " " << dir[1] << " " << dir[2] << " " << "0" << std::endl;
				ofs << "$track " << neutrino << " "  << totalenergy-sqrt(momentum*momentum+mass*mass) << " " << -dir[0] << " " << -dir[1] << " " << -dir[2] << " " << "0" << std::endl;
				ofs << "$end" << std::endl;

				
			}
			ofs << "$ stop" << std::endl;
		
		  }		
}
