create table player
(
player_id int NOT NULL,
player_name text,
dob date,
batting_hand text,
bowling_skill text,
country_name text,
PRIMARY KEY(player_id)
);

create table team
(
team_id int NOT NULL,
name text,
PRIMARY KEY(team_id)
);

create table match
(
match_id int NOT NULL,
team_1 int,
team_2 int,
match_date date,
season_id int CHECK(season_id >=1 AND season_id<=9),
venue text,
toss_winner int,
toss_decision text,
win_type text,
win_margin int,
outcome_type text,
match_winner int,
man_of_the_match int,
PRIMARY KEY(match_id)
);

create table player_match
(
match_id int NOT NULL,
player_id int NOT NULL,
role text,
team_id int,
PRIMARY KEY(match_id,player_id)
);

create table ball_by_ball
(
match_id int NOT NULL,
over_id int NOT NULL CHECK(over_id >=1 AND over_id<=20),
ball_id int NOT NULL CHECK(ball_id >=1 AND ball_id<=9),
innings_no int NOT NULL CHECK(innings_no >=1 AND innings_no<=4),
team_batting int,
team_bowling int,
striker_batting_position int,
striker int,
non_striker int,
bowler int,
PRIMARY KEY(match_id,over_id,ball_id,innings_no)
);

create table batsman_scored
(
match_id int NOT NULL,
over_id int NOT NULL CHECK(over_id >=1 AND over_id<=20),
ball_id int NOT NULL CHECK(ball_id >=1 AND ball_id<=9),
runs_scored int,
innings_no int NOT NULL CHECK(innings_no >=1 AND innings_no<=4),
PRIMARY KEY(match_id,over_id,ball_id,innings_no)
);

create table wicket_taken
(
match_id int NOT NULL,
over_id int NOT NULL CHECK(over_id >=1 AND over_id<=20),
ball_id int NOT NULL CHECK(ball_id >=1 AND ball_id<=9),
player_out int,
kind_out text,
innings_no int NOT NULL CHECK(innings_no >=1 AND innings_no<=4),
PRIMARY KEY(match_id,over_id,ball_id,innings_no)
);

create table extra_runs
(
match_id int NOT NULL,
over_id int NOT NULL CHECK(over_id >=1 AND over_id<=20),
ball_id int NOT NULL CHECK(ball_id >=1 AND ball_id<=9),
extra_type text,
extra_runs int,
innings_no int NOT NULL CHECK(innings_no >=1 AND innings_no<=4),
PRIMARY KEY(match_id,over_id,ball_id,innings_no)
);


