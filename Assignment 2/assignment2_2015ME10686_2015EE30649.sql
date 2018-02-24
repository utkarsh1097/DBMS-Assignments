--1--

SELECT player_name FROM player WHERE batting_hand='Left-hand bat' AND country_name='England' ORDER BY player_name;

--2--

select player_name, extract(year from age(timestamp '2018-02-12', dob)) as player_age from player where bowling_skill = 'Legbreak googly' and extract(year from age(timestamp '2018-02-12', dob)) >= 28 order by player_age desc, player_name;

--3--

SELECT match_id,toss_winner FROM match WHERE toss_decision='bat' ORDER BY match_id;

--4-- 

select over_id, t_runs_scored+extra_runs as runs_scored from (select over_id, innings_no, sum(coalesce(runs_scored, 0)) as t_runs_scored, sum(coalesce(extra_runs, 0)) as extra_runs from batsman_scored natural full outer join extra_runs where match_id = 335987 group by over_id, innings_no) as temp_table where t_runs_scored+extra_runs <= 7 order by runs_scored desc, over_id;

--5--

SELECT DISTINCT player_name FROM player WHERE player_id IN (SELECT player_out FROM wicket_taken WHERE kind_out='bowled') ORDER BY player_name;

--6--

select match_id, team_1_table.team_1 as team_1, team_2_table.team_2 as team_2, winning_team_name, win_margin from (select team_id, name as team_1 from team) AS team_1_table, (select team_id, name as team_2 from team) AS team_2_table, (select team_id, name as winning_team_name from team) AS winning_team_table, match where team_1_table.team_id = match.team_1 and team_2_table.team_id = match.team_2 and winning_team_table.team_id = match.match_winner and win_margin >= 60 order by win_margin, match_id;

--7--

SELECT player_name FROM player WHERE batting_hand='Left-hand bat' AND date_part('year',age(timestamp '2018-02-12',dob)) < 30  ORDER BY player_name;									

--8--

select match_id, t_runs_scored+extra_runs as total_runs from (select match_id, sum(coalesce(runs_scored, 0)) as t_runs_scored, sum(coalesce(extra_runs, 0)) as extra_runs from batsman_scored natural full outer join extra_runs group by match_id) as temp_table order by match_id;

--9--

select match_id, maximum_runs, player_name from (SELECT distinct temp6.match_id, temp6.over_id, maximum_runs,temp6.over_id, player_name FROM player,ball_by_ball,(SELECT temp4.match_id,temp4.over_id,temp4.innings_no,temp5.max AS maximum_runs FROM (SELECT match_id,over_id,innings_no,sum(runs) FROM ((SELECT match_id,over_id,innings_no ,runs_scored AS runs FROM batsman_scored AS temp1) UNION ALL (SELECT match_id,over_id,innings_no , extra_runs AS runs FROM extra_runs AS temp2) ) AS temp3 GROUP BY match_id,over_id,innings_no ) AS temp4 , (SELECT match_id, max(sum) FROM (SELECT match_id,over_id,innings_no,sum(runs) FROM ((SELECT match_id,over_id,innings_no ,runs_scored AS runs FROM batsman_scored AS temp1) UNION ALL (SELECT match_id,over_id,innings_no , extra_runs AS runs FROM extra_runs AS temp2) ) AS temp3 GROUP BY match_id,over_id,innings_no ) AS temp4 GROUP BY match_id ) AS temp5 WHERE temp5.match_id=temp4.match_id AND temp5.max=temp4.sum )AS temp6 WHERE ball_by_ball.match_id=temp6.match_id AND ball_by_ball.over_id=temp6.over_id AND ball_by_ball.innings_no=temp6.innings_no AND player_id=bowler ORDER BY match_id,over_id) as u;

--10--

select player_name, count(kind_out = 'run out' OR NULL) as number from wicket_taken full outer join player on player_id = player_out group by player_id order by number desc, player_name;

--11--

SELECT * FROM ( SELECT kind_out AS out_type,COUNT(player_out) AS number FROM wicket_taken GROUP BY kind_out) AS foo ORDER BY number DESC, out_type ASC;	

--12-- (not sure how it worked out)

select name, number from (select team_id, count(man_of_the_match) as number from player_match, match where man_of_the_match = player_id and player_match.match_id = match.match_id group by team_id) as temp_table, team where temp_table.team_id = team.team_id order by name; 

--13--

SELECT venue FROM (SELECT venue, SUM(extra_runs) as total FROM extra_runs NATURAL JOIN match WHERE extra_type = 'wides' GROUP BY venue) AS foo WHERE total IN (SELECT MAX(total) FROM (SELECT venue, SUM(extra_runs) as total FROM extra_runs NATURAL JOIN match WHERE extra_type = 'wides' GROUP BY venue) AS foo) ORDER BY venue LIMIT 1;

--14--

select venue from match group by venue order by count((toss_decision = 'field' and toss_winner = match_winner) or null)+count((toss_decision = 'bat' and toss_winner != match_winner) or null) desc, venue;

--15--

SELECT player_name FROM player WHERE player_id IN (SELECT bowler FROM (SELECT bowler,num_out,num_runs,((num_runs)*1000)/num_out AS bowling_average FROM (SELECT bowler,COUNT(kind_out) as num_out,( SUM(COALESCE(runs_scored,0)) + SUM(COALESCE(extra_runs,0)) ) AS num_runs FROM extra_runs NATURAL FULL OUTER JOIN batsman_scored NATURAL FULL OUTER JOIN wicket_taken NATURAL FULL OUTER JOIN ball_by_ball GROUP BY bowler ) AS foo WHERE num_out > 0 ) AS foo WHERE bowling_average IN (SELECT MIN(bowling_average) AS minimum FROM (SELECT bowler,num_out,num_runs,((num_runs)*1000)/num_out AS bowling_average FROM (SELECT bowler,COUNT(kind_out) as num_out,( SUM(COALESCE(runs_scored,0)) + SUM(COALESCE(extra_runs,0)) ) AS num_runs FROM extra_runs NATURAL FULL OUTER JOIN batsman_scored NATURAL FULL OUTER JOIN wicket_taken NATURAL FULL OUTER JOIN ball_by_ball GROUP BY bowler ) AS foo WHERE num_out > 0 ) AS foo ) ) ORDER BY player_name;

--16-- (count = 128) (confirmed from Prakhar, confirm from someone else)

select player_name, name from team, player, (select player_id, match_winner from match, player_match where match.match_id = player_match.match_id and role='CaptainKeeper' and match_winner = team_id) as temp_table where player.player_id = temp_table.player_id and team.team_id = temp_table.match_winner order by player_name, name;

--17--

SELECT player_name,players_total_runs AS runs_scored FROM (SELECT player_id,player_name, SUM(runs_scored) AS players_total_runs FROM player JOIN batsman_scored NATURAL LEFT OUTER JOIN ball_by_ball ON player_id=striker WHERE player_id IN (SELECT striker FROM (SELECT striker,MAX(runs_match) as max_runs_match FROM (SELECT striker,match_id,SUM(runs_scored) AS runs_match FROM batsman_scored NATURAL LEFT OUTER JOIN ball_by_ball GROUP BY striker,match_id) AS foo GROUP BY striker  ) AS foo WHERE max_runs_match >=50) GROUP BY player_id) AS foo ORDER BY players_total_runs DESC , player_name ASC ;

--18-- (count = 7) (confirmed from Prakhar, confirm from someone else)

select player_name from player, (select striker, runs_scored from (select match_id, team_batting, striker, sum(runs_scored) as runs_scored from batsman_scored natural full outer join ball_by_ball group by match_id, team_batting, striker) as temp_table, match where match.match_id = temp_table.match_id and team_batting != match_winner) as temp2_table where player.player_id = striker and runs_scored >= 100 order by player_name;

--19--

SELECT match_id ,venue FROM match WHERE (team_1=1 OR team_2=1) AND match_winner != 1 ORDER BY match_id ;

--20--

select player_name from player, (select striker, round(sum(runs_scored)/count(temp_table.match_id), 3) as average from (select match_id, striker, sum(runs_scored) as runs_scored from batsman_scored natural full outer join ball_by_ball group by match_id, striker) as temp_table, match where match.match_id = temp_table.match_id and season_id = 5 group by striker) as temp2_table where striker = player_id  order by average desc, player_name limit 10;

--21--

select country_name from (select country_name, rank() over (order by country_average desc) as rank from (select player.country_name, round(sum(average)/count, 3) as country_average from player, (select country_name, count(country_name) as count from player group by country_name) as temp4_table, (select striker, round(sum(runs_scored)/count(temp_table.match_id), 3) as average from (select match_id, striker, sum(runs_scored) as runs_scored from batsman_scored natural full outer join ball_by_ball group by match_id, striker) as temp_table, match where match.match_id = temp_table.match_id group by striker order by average desc) as temp2_table where player_id = striker and temp4_table.country_name = player.country_name group by player.country_name, count) as temp3_table) as temp_4 where rank <= 5 order by rank, country_name;