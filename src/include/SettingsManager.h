#ifndef SETTINGSMANAGER
#define SETTINGSMANAGER

//! Class to handle all the settings in the program. Can only instance one SettingsManager-class in the whole program. 
class SettingsManager {
private:
	int population_size_;
	int max_generations_;
	float crossover_ratio_;
	float elitism_ratio_;
	float mutation_ratio_;

	SettingsManager();
	~SettingsManager(void); 

	static SettingsManager* m_pInstance;

public:

	static SettingsManager* Instance();

	void setPopulationSize(int population_size);
	void setMaxGenerations(int max_generations);
	void setCrossover(float crossover_ratio);
	void setElitism(float elitism_ratio);
	void setMutation(float mutation_ratio);

	int getPopulationSize();
	int getMaxGenerations();
	float getCrossover();
	float getElitism();
	float getMutation();

};




#endif // SETTINGSMANAGER