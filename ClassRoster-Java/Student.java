
public class Student {
	private String id;
	private int cla;
	private int ola;
	private int quiz;
	private int homeWork;
	private int exam;
	private int bonus;
	private int total;
	private char finalGrade;
	
	public Student(String i, int c, int o, int q, int h, int e, int b) {
		id = i;
		cla = c;
		ola = o;
		quiz = q;
		homeWork = h;
		exam = e;
		bonus = b;
		
		total = cla + ola + quiz + homeWork + exam + bonus;
		
		if (total >= 90){
			finalGrade = 'A';
		} else if (total < 90 && total >= 80) {
			finalGrade = 'B';
		} else if (total < 80 && total >= 70) {
			finalGrade = 'C';
		} else if (total < 70 && total >= 60) {
			finalGrade = 'D';
		} else {
			finalGrade = 'F';
		}
	}
	
	public String getID () {
		return this.id;
	}
	public int getCLA() {
		return this.cla;
	}	
	public int getOLA() {
		return this.ola;
	}	
	public int getQuiz() {
		return this.quiz;
	}	
	public int getHomework() {
		return this.homeWork;
	}	
	public int getExam() {
		return this.exam;
	}	
	public int getBonus() {
		return this.bonus;
	}
	public int getTotal() {
		return this.total;
	}
	public char getFinal() {
		return this.finalGrade;
	}

	public void SetID (String id) {
		this.id = id;
		this.reTotal();
		this.reGrade();
	}
	public void setCLA(int c) {
		this.cla = c;
		this.reTotal();
		this.reGrade();
	}
	public void setOLA(int o) {
		this.ola = o;
		this.reTotal();
		this.reGrade();
	}
	public void setQuiz(int q) {
		this.quiz = q;
		this.reTotal();
		this.reGrade();
	}
	public void setHomeWork(int h) {
		this.homeWork = h;
		this.reTotal();
		this.reGrade();
	}
	public void setExam(int e) {
		this.exam = e;
		this.reTotal();
		this.reGrade();
	}
	public void setBonus(int b) {
		this.bonus = b;
		this.reTotal();
		this.reGrade();
	}
	
	public void reTotal() {
		this.total = this.cla + this.ola + this.quiz + this.homeWork + this.exam + this.bonus;
		System.out.println("Total Set!");
	}
	public void reGrade() {
		if (this.total >= 90){
			finalGrade = 'A';
		} else if (this.total < 90 && this.total >= 80) {
			finalGrade = 'B';
		} else if (this.total < 80 && this.total >= 70) {
			finalGrade = 'C';
		} else if (this.total < 70 && this.total >= 60) {
			finalGrade = 'D';
		} else {
			finalGrade = 'F';
		}
		System.out.println("Final Grade Set!");
	}
	
	public void displayStudent() {
		System.out.printf("%7s %6d %6d %6d %6d %6d %6d %6d %6c\n", this.id, this.cla, this.ola,
							this.quiz, this.homeWork, this.exam, this.bonus, this.total, this.finalGrade);
	}
	
	
}
